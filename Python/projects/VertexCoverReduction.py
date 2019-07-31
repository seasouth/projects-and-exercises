import sys
import collections
import networkx as nx


"""
This code is for the following tasks in 
Part 2: Vertex Cover – Reduction and Verification:

Task I
Task III.2


"""

def main():
    filename = sys.argv[1]
    k = int(sys.argv[2])

    G = load_graph(filename)
    

    
    n = len(G)

    graph = nx.Graph()
    

    """
    
    This code should print  "yes"/"no" if there's a vertex cover of size k. 
    (As long as there's a vertex cover of size k, print "yes"
     Note that this code prints only one "yes" or "no")

    Also, the code should write the complement graph of the input to a .txt file.
    You can write the graph to .txt with this command: 
    write_graph("complement.graph", YOUR_complement GRAPH)
    

    This code should use the "reduction from clique" idea to come up with 
    the answer. 
    
    You can find cliques with this command:   nx.find_cliques(graph)
    """
    
    G_prime = collections.defaultdict(set)
    
    for i in G:
        #print(str(i) + " " + str(G[i]))
        for j in G:
            if j not in G[i]:
                if j is not i:
                    G_prime[i].add(j)
    
    #print(" ")
    #for i in G_prime:
    #    print(str(i) + " " + str(G_prime[i]))
    #print(" ")
    
    graph = nx.convert.to_networkx_graph(G_prime)
    k_prime = n - k
    
    cliques = list(nx.find_cliques(graph))
    
    maximum_clique = 0
    for i in range(len(cliques)):
        #print(str(cliques[i]) + " " + str(len(cliques[i])))
        if len(cliques[i]) > maximum_clique:
            maximum_clique = len(cliques[i])
    #print()
    if k_prime <= maximum_clique:
        print("yes")
    else:
        print("no")
    
    write_graph("complement.graph", G_prime)


def write_graph(filename, adj_list):
    with open(filename, "w") as fout:
        for u in adj_list:
            for v in adj_list[u]:
                if u < v:
                    fout.write(str(u)+" "+str(v)+"\n")


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
