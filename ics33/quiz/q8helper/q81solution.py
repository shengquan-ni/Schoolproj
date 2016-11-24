from performance import Performance
from goody import irange
from graph_goody import random_graph,spanning_tree

# Put script below to generate data for Problem #1
# In case you fail, the data appears in sample8.pdf in the helper folder
for i in range(8):
    size=(2**i)*1000
    g=random_graph(size,lambda x:x*10)
    p=Performance(lambda :spanning_tree(g),lambda :None,5,'\n\nSpanning Tree of size ' + str(size))
    p.evaluate()
    p.analyze()
