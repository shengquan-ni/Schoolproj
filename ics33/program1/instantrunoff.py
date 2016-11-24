# Submitter: shenqgun(Shengquan, Ni)
# Partner  : yangguah(Yangguang, He)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
import goody
from collections import defaultdict


def read_voter_preferences(file : open):
    return {i[0]:i[1:] for i in (j.strip().split(';') for j in file.readlines())}
    


def dict_as_str(d : {None:None}, key : callable=None, reverse : bool=False) -> str:
    return ''.join('  '+str(i)+' -> '+str(d[i])+'\n' for i in sorted(d.keys(),key=key,reverse=reverse))


def evaluate_ballot(vp : {str:[str]}, cie : {str}) -> {str:int}:
    result=defaultdict(int)
    for i in vp:
        for k in vp[i]:
            if k in cie:
                result[k]+=1
                break
    return result


def remaining_candidates(vd : {str:int}) -> {str}:
    return set(i for i in vd.keys() if vd[i]!=min(vd.values()))


def run_election(vp_file : open) -> {str}:
    v,count=read_voter_preferences(vp_file),0
    print('\n'+'Voting Preferences\n'+dict_as_str(v))
    c=set(list(v.values())[0])
    while len(c)>1:
        temp,count=evaluate_ballot(v,c),count+1
        print('Vote count on ballot #{:} with candidates (alphabetical order);remaining candidate set = {:}\n'.format(count,c if len(c)>0 else {})+\
              ''.join('{} -> {}\n'.format(i,j) for i,j in sorted(temp.items(),key=lambda x:x[0]))+'\n')
        print('Vote count on ballot #{:} with candidates (numerical order);remaining candidate set = {:}\n'.format(count,c if len(c)>0 else {})+\
              ''.join('{} -> {}\n'.format(i,j) for i,j in sorted(temp.items(),key=lambda x:x[1]))+'\n')
        c=remaining_candidates(temp)
    print('Winner is {:}'.format(c if len(c)>0 else {}))
    return c
    

  
  
  
  
    
if __name__ == '__main__':
    # Write script here
    run_election(goody.safe_open('Enter the name of any file with voter preferences','r','ERROR'))     
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc2.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
