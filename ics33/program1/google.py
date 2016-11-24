# Submitter: shenqgun(Shengquan, Ni)
# Partner  : yangguah(Yangguang, He)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
import prompt 
from goody       import safe_open,irange
from collections import defaultdict # Use defaultdict for prefix and query


def all_prefixes(fq : (str,)) -> {(str,)}:
    return set([fq[:i] if i!=0 else fq for i in range(len(fq))])


def add_query(prefix : {(str,):{(str,)}}, query : {(str,):int}, new_query : (str,)) -> None:
    for i in all_prefixes(new_query):
        prefix[i].add(new_query)
    query[new_query]+=1
    


def read_queries(open_file : open) -> ({(str,):{(str,)}}, {(str,):int}):
    p,q = defaultdict(set), defaultdict(int)
    for i in open_file.readlines():
        add_query(p,q,tuple(i.split()))
    return p,q


def dict_as_str(d : {None:None}, key : callable=None, reverse : bool=False) -> str:
    return ''.join('  {} -> {}\n'.format(i,d[i]) for i in sorted(d,key=key,reverse=reverse))


def top_n(a_prefix : (str,), n : int, prefix : {(str,):{(str,)}}, query : {(str,):int}) -> [(str,)]:
    return [i[0] for i in sorted([(i,query[i]) for i in query.keys() if i[:len(a_prefix)]==a_prefix],key=lambda x:(-x[1],x[0]))][:n]





# Script

if __name__ == '__main__':
    # Write script here
    p,q=read_queries(safe_open('Enter the name of any file with the full queries','r','ERROR'))
    while True:
        print('\nPrefix dictionary:\n'+dict_as_str(p,lambda x:(len(x),x)))
        print('\nQuery dictionary:\n'+dict_as_str(q,lambda x:(-q[x],x)))
        p_input=input('Enter any prefix (or quit): ')
        if p_input=='quit':break
        else: print('  Top 3 (or fewer) full queries = {}'.format(top_n(tuple(p_input.split()),3,p,q)))
        q_input=input('Enter any full query (or quit): ')
        if q_input=='quit':break
        else: add_query(p,q,tuple(q_input.split()))
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc5.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
