from equivalence import EquivalenceClass
from graph import Graph
from random import randrange,randint


# Return a random graph_original with nodes named by str of ints 0 to n-1
# Calling random_graph(100,lambda n : 10*n) creates a graph with about 100 nodes
#   and 1,000 (10 times as many) undirected edges.
def random_graph (n : int, edges_to_create: callable) -> Graph:
    g = Graph()
    for _i in range(int(edges_to_create(n))):
        n1 = str(randrange(n))
        n2 = str(randrange(n))
        if n1 != n2 and not (n1,n2) in g:
            v = randint(1,n)
            g[n1,n2] = v
            g[n2,n1] = v
    return g


# Return the spanning tree of a Graph: the minimal set of edges
#   that allow reaching any node from any other node; assumes
#   the edges are undirected (as they are in random_graph above)
def spanning_tree(g : Graph) -> {(str,str,int)}:
    answer = set()
    edges = sorted( (e[2],e[0],e[1]) for e in g if len(e) != 1) 
    components = EquivalenceClass(g.all_nodes())
    n = len(g.all_nodes())
    for v,o,d in edges:
        if n == 1:
            return answer
        if not components.in_same_class(o, d):
            answer.add((o,d,v))
            components.merge_classes_containing(o, d)
            n -= 1
    return answer