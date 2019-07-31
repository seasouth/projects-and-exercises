"""
 A nondeterministic finite-state automaton that
 recognizes strings with 0 as the next-to-last
 character.
"""

"""
 The current set of states, encoded bitwise:
 state i is represented by the bit 1<<i.
"""
stateSet = 0

"""
 Reset the current state set to {the start state}.
"""


def reset():
    global stateSet
    stateSet = 1 << 0


"""
 The transition function represented as an array.
 The set of next states from a given state s and
 character c is at delta[s,c-'0'].
    delta[q0,0] = {q0}
    delta[q0,1] = {q0,q1}
    delta[q1,0] = {q2}
    delta[q1,1] = {q2}
    delta[q2,0] = {}
    delta[q2,1] = {}
"""
delta = [[1 << 0 | 1 << 1, 1 << 0],
         [1 << 2, 0],
         [1 << 2, 1 << 2]]


"""
 Make one transition from state-set to state-set on
 each char in the given string.
 @param inp the String to use
"""


def process(inp):
    global stateSet
    for i in range(len(inp)):
        c = inp[i]
        nextSS = 0  # next state set, initially empty
        for s in range(3):  # for each state s
            if (stateSet & (1 << s)) != 0:  # if maybe in s
                try:
                    nextSS |= delta[s][int(c)]
                except():
                    # in effect, nextSS |= 0
                    pass
        stateSet = nextSS  # new state set after c


"""
 Test whether the NFA accepted the string.
 @return true if the final set includes
 an accepting state.
"""


def accepted():
    global stateSet
    return (stateSet & (1 << 2)) != 0
