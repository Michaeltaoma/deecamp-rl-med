import numpy as np


def reward_function_duel_ddqn(state: list) -> float:
    # to know where things is
    hr, rr, p = state[0], state[1], state[2]
    cp, chr, crr = 1 / 3, 1 / 3, 1 / 3
    return cp * duel_ddqn_p_return(p) + chr * duel_ddqn_hr_return(hr) \
           + crr * duel_ddqn_rr_return(rr)


def duel_ddqn_hr_return(hr: float) -> float:
    return (2 / (1 + np.exp(-(hr - 60)))) - (2 / (1 + np.exp(-(hr - 100)))) - 1


def duel_ddqn_rr_return(rr: float) -> float:
    return (2 / (1 + np.exp(-(rr - 12)))) - (2 / (1 + np.exp(-(rr - 20)))) - 1


def duel_ddqn_p_return(p: float) -> float:
    return 1 - (2 * p) / 10
