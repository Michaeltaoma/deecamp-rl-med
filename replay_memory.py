import numpy as np
import datetime
import psycopg2
import sys
import agent_helper
import random


class ReplayMemory(object):
    def __init__(self) -> None:
        try:
            con = psycopg2.connect(database='mimic4', user='michaelma',
                                   password='12154877',
                                   options=f'-c search_path=clean_align')
            self.conn = con
        except psycopg2.DatabaseError as e:
            print(f'Error {e}')
            sys.exit(1)
        cur = self.conn.cursor()
        cur.execute("SELECT 'clean_align.tran_id' FROM clean_align")
        self.length = int(cur.rowcount)
        self.dim = 3

    def length(self) -> int:
        return self.length

    def uniform_sample(self, batch_size: int, continuous: bool = False) -> list:
        if batch_size > self.length:
            pass
        if continuous:
            rand = random.randint(0, self.length - batch_size)
            return self.batch_from_id(range(rand, rand + batch_size))
        else:
            indexes = (np.random.choice(np.arange(self.length), size=batch_size, replace=False) + 1).tolist()
        return self.batch_from_id(indexes)

    def batch_from_id(self, state_list: list) -> list:
        batch_state_list = list()
        for state_id in state_list:
            sa = self.get_states_action_from_id(state_id)
            state = sa["state"]
            action = ml_cut(sa["action"])
            next_state = sa["next_state"] if sa["next_state"] is not None else np.random.rand(self.dim)
            end = True if sa["next_state"] is None else False
            reward = agent_helper.reward_function_duel_ddqn(state)
            local_state_tuple = (state, next_state, action, reward, end)
            batch_state_list.append(local_state_tuple)
        return batch_state_list

    def get_states_action_from_id(self, state_id: int) -> dict:
        cur = self.conn.cursor()
        state_action = dict()
        if int != -1:
            s = 'SELECT hr, rr, pl, morphine, nhr, nrr, npl, nmorphine FROM clean_align WHERE clean_align.tran_id = %s'
            cur.execute(s, (state_id,))
            sa = cur.fetchone()
            state_action["state"] = np.array(sa[:3])
            state_action["action"] = sa[3]
            state_action["next_state"] = np.array(sa[4:-1]) if sa[4] is not None else None
        else:
            state_action["state"] = np.random.rand(3)
            state_action["action"] = -1
            state_action["next_state"] = np.random.rand(3)
        return state_action


def ml_cut(ml):
    if ml == 0:
        cut_ml = 0
    elif 0 < ml <= 1:
        cut_ml = 1
    elif 1 < ml <= 2:
        cut_ml = 2
    elif 2 < ml <= 3:
        cut_ml = 3
    elif 3 < ml <= 4:
        cut_ml = 4
    elif 4 < ml <= 5:
        cut_ml = 5
    elif 5 < ml <= 6:
        cut_ml = 6
    elif 6 < ml <= 7:
        cut_ml = 7
    elif 7 < ml <= 8:
        cut_ml = 8
    elif 8 < ml <= 9:
        cut_ml = 9
    elif 9 < ml <= 10:
        cut_ml = 10
    elif 10 < ml <= 15:
        cut_ml = 11
    elif 15 < ml <= 20:
        cut_ml = 12
    elif ml > 20:
        cut_ml = 13
    else:
        cut_ml = -1
    return float(cut_ml)


def an_hour_after(current_time: datetime.datetime) -> datetime.datetime:
    return current_time + datetime.timedelta(hours=1)


