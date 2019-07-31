"""
A nondeterministic finite-state automaton that
recognizes strings of 0s and 1s with 1 as the
next-to-last character.

This assignment is also going to revisit some
ideas of using Classes in Python, so will be
different from the example code in R1.CH6.
"""


class State():
    def __init__(self, name, is_start_state, is_final_state):
        """
        *** Implement your constructor here, it needs to setup 4 private attributes: ***
        1. name             , the name of the state, i.e. q0
        2. is_start_state   , the name of the state, i.e. True if is start state
        3. is_final_state   , the name of the state, i.e. False if not final state
        4. transitions      , the transition table, contents are filled by add_transitions()
        """
        self.name = name
        self.is_start_state = is_start_state
        self.is_final_state = is_final_state
        self.transitions = {}
    def add_transitions(self, string, target_states):
        '''
        *** Implement your code here to put values to the transition table ***
        '''
        k = string
        v = target_states
        self.transitions[k] = v


"""
The following is an example building an NFA that:
    q0 is start state
    q1 is final state
    q0 goes to [q0] if reads 0
    q0 goes to [q0,q1] if reads 1

So if you run python NFA1Filter.py and type:
00 it would return fail
01 it would return accept


***Implement your states and transition functions here***
***You should change the following line 48~53 to the NFA assigned***
"""

q0 = State("q0", True, False)
q1 = State("q1", False, False)
q2 = State("q2", False, True)
q0.add_transitions("0", [q0, q1])
q0.add_transitions("1", [q0])
q1.add_transitions("0", [q2])
q2.add_transitions("0", [q2])
q2.add_transitions("1", [q2])

states = [q0, q1, q2]


"""
 Test whether there is some path for the NFA to
 reach an accepting state from the given state,
 reading the given string at the given character
 position.
 @param state the current state
 @param inp the input string
 @param pos index of the next char in the string
 @return true if the NFA accepts on some path
"""


def accept_step(state, inp, pos):
    if pos == len(inp):  # if no more to read
        return state.is_final_state   # accept if the reached state is final state
    c = inp[pos]    # get char
    pos = pos + 1;
    try:
        nextStates = state.transitions[c]
    except:
        return False    # no transition, just reject

    # At this point, nextStates is an array of 0 or
    # more next states.  Try each move recursively;
    # if it leads to an accepting state return true.
    """
    *** Implement your recursive function here, it should read state in nextStates
    one by one, and run accept_step() again with different parameters ***
    """
    for item in nextStates:
        if accept_step(item, inp, pos):
            return True
    return False    # all moves fail, return false


"""
 Test whether the NFA accepts the string.
 @param in the String to test
 @return true if the NFA accepts on some path
"""


def accepts(str_input):
    return accept_step(states[0], str_input, 0)  # start in q0 at char 0
