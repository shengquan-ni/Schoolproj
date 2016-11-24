import re
from goody import irange
from collections import defaultdict

# Before running the driver on the bsc.txt file, ensure you have put a regular
#   expression pattern in the files repattern1a.txt, repattern1b.txt, and
#   repattern2a.txt. 

#result in ascending order (duplicates allowed)
def pages (page_spec : str) -> [int]:
    assert all([re.match('^[1-9]\d*(:[1-9]\d*|-[1-9]\d*)?\s*$',i) for i in page_spec.strip().split(',')])\
    and all(k[0]<=k[1] for k in [i.split('-') for i in page_spec.strip().split(',') if i.find('-')!=-1])
    result=[]
    for i in page_spec.strip().split(','):
        if i.find('-')!=-1:result.extend([i for i in range(int(i.split('-')[0]),int(i.split('-')[1])+1)])
        elif i.find(':')!=-1:result.extend([i for i in range(int(i.split(':')[0]),sum(int(k) for k in i.split(':'))+1)])
        else: result.append(int(i))
    return sorted(result)



def multi_search(pat_file : open, text_file : open) -> [(int,str,{int})]:
    parttens=[re.compile(i.rstrip()) for i in pat_file]
    return [(i+1,d.rstrip(),[k[0]+1 for k in enumerate(parttens) if k[1].search(d)])\
            for i,d in enumerate(text_file) if len([k[0]+1 for k in enumerate(parttens) if k[1].search(d)])] 





if __name__ == '__main__':
    print(multi_search(open("pats.txt"),open("texts.txt")))
    import driver
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
