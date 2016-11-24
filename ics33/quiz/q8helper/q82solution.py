import cProfile
from graph_goody import random_graph, spanning_tree
import pstats

# Put script below to generate data for Problem #2
# In case you fail, the data appears in sample8.pdf in the helper folder

g1,g2=random_graph(50000,lambda x:50000*10),random_graph(100000,lambda x:100000*10)
cProfile.run("spanning_tree(g1)","Profile50K")
pstats.Stats('Profile50K').sort_stats('ncalls').print_stats()
cProfile.run("spanning_tree(g2)","Profile100K")
pstats.Stats('Profile100K').sort_stats('tottime').print_stats()
