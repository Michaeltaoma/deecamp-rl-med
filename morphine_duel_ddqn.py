import torch
import torch.nn as nn
import random
from itertools import count
import torch.nn.functional as F
from tensorboardX import SummaryWriter
import replay_memory

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")


class QNetwork(nn.Module):
    def __init__(self):
        super(QNetwork, self).__init__()

        self.fc1 = nn.Linear(3, 64)
        self.relu = nn.ReLU()
        self.leakey = nn.LeakyReLU()
        self.fc_value = nn.Linear(64, 256)
        self.fc_adv = nn.Linear(64, 256)

        self.value = nn.Linear(256, 1)
        self.adv = nn.Linear(256, 14)

    def forward(self, state):
        y = self.leakey(self.fc1(state))
        value = self.leakey(self.fc_value(y))
        adv = self.leakey(self.fc_adv(y))

        value = self.value(value)
        adv = self.adv(adv)

        advAverage = torch.mean(adv, dim=1, keepdim=True)
        Q = value + adv - advAverage

        return Q

    def select_action(self, state):
        with torch.no_grad():
            Q = self.forward(state)
            action_index = torch.argmax(Q, dim=1)
        return action_index.item()


onlineQNetwork = QNetwork().to(device)
targetQNetwork = QNetwork().to(device)
targetQNetwork.load_state_dict(onlineQNetwork.state_dict())

optimizer = torch.optim.Adam(onlineQNetwork.parameters(), lr=1e-4)

GAMMA = 0.5
EXPLORE = 20000
INITIAL_EPSILON = 0.1
FINAL_EPSILON = 0.0001
REPLAY_MEMORY = 50000
BATCH = 32

UPDATE_STEPS = 4

epsilon = INITIAL_EPSILON
learn_steps = 0
writer = SummaryWriter('logs/ddqn_1')
begin_learn = False

episode_reward = 0

# onlineQNetwork.load_state_dict(torch.load('ddqn-policy.para'))

for epoch in count():

    episode_reward = 0
    for time_steps in range(200):
        p = random.random()
        done = True if p < epsilon else False

        if begin_learn is False:
            print('learn begin!')
            begin_learn = True
        learn_steps += 1
        if learn_steps % UPDATE_STEPS == 0:
            targetQNetwork.load_state_dict(onlineQNetwork.state_dict())
        replay = replay_memory.ReplayMemory()
        batch = replay.uniform_sample(BATCH, False)
        batch_state, batch_next_state, batch_action, batch_reward, batch_done = zip(*batch)

        batch_state = torch.FloatTensor(batch_state).to(device)
        batch_next_state = torch.FloatTensor(batch_next_state).to(device)
        batch_action = torch.FloatTensor(batch_action).unsqueeze(1).to(device)
        batch_reward = torch.FloatTensor(batch_reward).unsqueeze(1).to(device)
        batch_done = torch.FloatTensor(batch_done).unsqueeze(1).to(device)

        with torch.no_grad():
            onlineQ_next = onlineQNetwork(batch_next_state)
            targetQ_next = targetQNetwork(batch_next_state)
            online_max_action = torch.argmax(onlineQ_next, dim=1, keepdim=True)
            y = batch_reward + (1 - batch_done) * GAMMA * targetQ_next.gather(1, online_max_action.long())
        loss = F.mse_loss(onlineQNetwork(batch_state).gather(1, batch_action.long()), y)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        writer.add_scalar('loss', loss.item(), global_step=learn_steps)

        if epsilon > FINAL_EPSILON:
            epsilon -= (INITIAL_EPSILON - FINAL_EPSILON) / EXPLORE

        if done:
            break

    if epoch % 10 == 0:
        torch.save(onlineQNetwork.state_dict(), 'ddqn-policy.para')
        # print('Ep {}\tMoving average score: {:.2f}\t'.format(epoch, episode_reward))
        print("EPOCH: {}".format(epoch))
