import sys
import copy
import collections

"""
This code is for the following tasks in 
Part 2: Vertex Cover – Reduction and Verification:

Task II
Task III.I


"""

def main():
    gfilename = sys.argv[1]
    cfilename = sys.argv[2]
    k = int(sys.argv[3])

    graph = load_graph(gfilename)
    candidates = load_candidates(cfilename)
    
    """
    Your code here. (You can add your own helper functions elsewhere)
    This code should output "yes"/"no" for each candidate if it's a vertex cover of size k.
    (i.e. If there are 5 candidate, print 5 "yes"/"no", seperated by new lines)
    """

    for i in candidates:
        candidate = i
        if len(candidate) is not k:
            print("no")
        else:
            temp = copy.copy(graph)
            for j in candidate:
                temp.pop(j)
                high_degree = 0;
                for k in temp:
                    if j in temp[k]:
                        temp.get(k).remove(j)
                    if len(temp[k]) > high_degree:
                        high_degree = len(temp[k])
                if high_degree == 0:
                    temp.clear()
            if len(temp) is 0:
                print("yes")
            else:
                print("no")

def load_candidates(filename):
    candidates = []
    adj_list = collections.defaultdict(set)
    with open(filename, "r") as fin:
        for line in fin:
            candidates.append([int(v) for v in line.strip().split()])
    return candidates


def load_graph(filename):
    adj_list = collections.defaultdict(set)
    with open(filename, "r") as fin:
        for line in fin:
            u, v = [int(v) for v in line.strip().split()]
            adj_list[u].add(v)
            adj_list[v].add(u)
    return adj_list

if __name__ == "__main__":
    main()
