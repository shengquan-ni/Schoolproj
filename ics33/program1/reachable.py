# Submitter: shenqgun(Shengquan, Ni)
# Partner  : yangguah(Yangguang, He)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
import goody
import prompt
from collections import defaultdict


def read_graph(file : open) -> {str:{str}}:
    result=defaultdict(set)
    for i in (x.strip().split(';') for x in file.readlines()):
        result[i[0]].add(i[1])
    return result

def graph_as_str(graph : {str:{str}}) -> str:
    return ''.join('  '+str(x[0])+' -> '+str(sorted(x[1]))+'\n' for x in sorted(graph.items()))

        
def reachable(graph : {str:{str}}, start : str) -> {str}:
    result,explore=set(start),list(graph[start])
    while len(explore)>0:
        temp=explore.pop()
        result.add(temp)
        if temp in graph.keys():
            explore.extend(list(graph[temp]-result))
    return result
    
    
    
if __name__ == '__main__':
    # Write script here
    g=read_graph(goody.safe_open('Enter the name of a file with a graph','r','ERROR'))
    print('\n'+'Graph: source -> [destination] edges\n'+graph_as_str(g))
    while True:
        s=input('Enter the name of a starting node: ')
        if s=='quit':break
        elif s in g.keys():print('From {} the reachable nodes are {}'.format(s,reachable(g,s)))
        else:print("Entry Error: '{}';  Illegal: not a source node\nPlease enter a legal String".format(s))
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc1.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
    #read_graph(driver
