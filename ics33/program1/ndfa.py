# Submitter: shenqgun(Shengquan, Ni)
# Partner  : yangguah(Yangguang, He)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
import goody
from collections import defaultdict


def read_ndfa(file : open) -> {str:{str:{str}}}:
   result={}
   for i in (j.strip().split(';') for j in file.readlines()):
      temp=defaultdict(set)
      for k in range(0,len(i[1:]),2):
         temp[i[1:][k]].add(i[1:][k+1])
      result[i[0]]=temp
   return result
      
      


def ndfa_as_str(ndfa : {str:{str:{str}}}) -> str:
   return ''.join('  {} transitions: {}\n'.format(i,list((k[0],sorted(list(k[1]))) for k in sorted(list(ndfa[i].items())))) for i in sorted(ndfa.keys()))

       
def process(ndfa : {str:{str:{str}}}, state : str, inputs : [str]) -> [None]:
   result,state=[state],set([state])
   flatten=lambda l:sum((flatten(i) for i in l),[]) if type(l)==list else [l]
   for i in inputs:
      if state==set():break
      state=set(flatten([list(ndfa[k][i]) for k in state if (k in ndfa.keys() and i in ndfa[k].keys())]))
      result.append((i,state))
   return result


def interpret(result : [None]) -> str:
   return 'Start state = {}\n'.format(result[0])+\
          ''.join('  Input = {}; {}\n'.format(i[0],'new possible states = '+str(sorted(list(i[1])))) for i in result[1:])+\
          'Stop state(s) = {}\n'.format(sorted(list(result[-1][-1])))





if __name__ == '__main__':
    # Write script here
    ndfa=read_ndfa(goody.safe_open('Enter the name of any file with a non-deterministic finite automaton','r','ERROR'))
    print("\nNon-Deterministic Finite Automaton's Description\n"+ndfa_as_str(ndfa))
    for i in (line.strip().split(';') for line in goody.safe_open('Enter the name of any file with the start-state and inputs','r','ERROR')):
        print('\nStarting new simulation')
        print(interpret(process(ndfa,i[0],i[1:])))    
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc4.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
