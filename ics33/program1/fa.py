# Submitter: shenqgun(Shengquan, Ni)
# Partner  : yangguah(Yangguang, He)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
import goody


def read_fa(file : open) -> {str:{str:str}}:
    return {i[0]:{i[1:][k]:i[1:][k+1] for k in range(0,len(i[1:]),2)} for i in (j.strip().split(';') for j in file.readlines())}


def fa_as_str(fa : {str:{str:str}}) -> str:
    return ''.join('  {} transitions: {}\n'.format(i,sorted(list(fa[i].items()))) for i in sorted(fa.keys()))

    
def process(fa : {str:{str:str}}, state : str, inputs : [str]) -> [None]:
    result=[state]
    for i in inputs:
        state=fa[state][i] if i in fa[state].keys() else None
        result.append((i,state))
    return result


def interpret(fa_result : [None]) -> str:
    return 'Start state = {}\n'.format(fa_result[0])+\
           ''.join('  Input = {}; {}\n'.format(i[0],'new state = '+str(i[1]) if i[1] else 'illegal input: simulation terminated') for i in fa_result[1:])+\
           'Stop state = {}\n'.format(fa_result[-1][-1])
    




if __name__ == '__main__':
    # Write script here
    fa=read_fa(goody.safe_open('Enter the name of any file with a finite automaton','r','ERROR'))         
    print("\nFinite Automaton's Description\n"+fa_as_str(fa))
    for i in (line.strip().split(';') for line in goody.safe_open('Enter the name of any file with the start-state and inputs','r','ERROR')):
        print('\nStarting new simulation')
        print(interpret(process(fa,i[0],i[1:])))
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc3.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
