#Shengquan Ni 46564157

from collections import defaultdict

 # Helper function used in testing; do not remove or modify
def palindrome(s : str) -> bool:
    return s == s[-1::-1]


def abs_of(f : callable) -> callable:
    return lambda x:abs(f(x))


def select(predicates : [callable]) -> callable:
    return lambda x:[i for i in x if all([j(i) for j in predicates])]


def talk(alist : [int]) -> [int]:
    assert len(alist)!=0 and all([type(i)==int for i in alist])
    func=lambda x,y,z,l: sum([[x-z,l[x]]],y) if x>=len(l)-1 else func(x+1,y,z,l) if l[x]==l[x+1] else func(x+1,sum([[x-z,l[x]]],y),x,l)
    return func(0,[],-1,alist)

def made_quota(db : {str:(str,int,int)}) -> {str}:
    return set([i for i in sorted(db) if all([j[1]<=j[2] for j in db[i]])])


def sales1(db : {str : (str,int,int)}) -> [str]:
    return [k[1] for k in sorted([(-sum(j[2] for j in db[i]),i) for i in db])]


def sales2(db : {str : (str,int,int)}) -> [(str,int)]:
    return sorted([(i,sum(j[2] for j in db[i])) for i in db],key=lambda x:(-x[1],x[0]))


def by_category(db : {str : (str,int,int)}) -> {str : (str,int,int)}:
    result=defaultdict(list)
    for i in db:
        for j in db[i]:
            result[j[0]].append((i,j[1],j[2]))
    for i in result: result[i].sort()
    return result


def category_leaders(db : {str : (str,int,int)}) -> [int,{str}]:
    result,bc=defaultdict(list),by_category(db)
    for i in bc:
        temp=max(j[2] for j in bc[i])
        result[i].extend([temp,set(k[0] for k in bc[i] if k[2]==temp)])
    return result


if __name__ == '__main__':
    from goody import irange
    # Feel free to test other cases as well
    
    print('Testing abs_of')
    f = abs_of(lambda x : 3*x+2)
    print( [(a,f(a)) for a in [-10, -5, 0, 5, 10]] )
    g = abs_of(lambda x : -x)
    print( [(a,g(a)) for a in [-10, -5, 0, 5, 10]] )
     
    print('\nTesting select')
    big_odd = select ([(lambda x : x%2 == 1), (lambda x : x > 5)]) 
    print( big_odd(range(1,10)) )
    scp = select([(lambda x : len(x) <=5),(lambda x : x[0] not in 'aeiou'),palindrome])
    print( scp(['rotator', 'redder', 'pepper', 'rotor', 'tiny', 'eye', 'mom', 'ere', 'radar', 'racecar', 'peep']) )

    print('\nTesting talk')
    seq = [1]
    print(1, seq)
    for i in irange(2,10):
        seq = talk(seq)
        print(i,seq)

    # For testing functions: none should mutate these dicts
    lexus = {'Rich': {('car', 10, 4), ('suv', 10, 12)},
             'Steve': {('crossover', 10, 12), ('car', 7, 8)},
             'Nancy': {('truck', 10, 5), ('car', 10, 8)},
             'Lori' : { ('suv', 10, 12), ('truck', 10, 10), ('car', 10, 15) } }
    
    ace =   {'Alex'  : {('hammer', 4, 7), ('saw', 6, 6)},
             'Mark'  : {('hammer', 6, 8), ('wrench', 7, 6)},
             'Bernie': {('pliers', 4, 5), ('screws', 4, 2)},
             'Mike'  : { ('pliers', 2, 3), ('screws', 4, 4), ('wrench', 3, 3) },
             'Katie' : { ('hammer', 1, 1), ('pliers', 2, 6), ('screws', 3, 5) } }

    ace2 =  {'Alex'  : {('hammer', 4, 6), ('saw', 6, 6)},
             'Mark'  : {('hammer', 6, 8), ('wrench', 7, 6)},
             'Bernie': {('pliers', 4, 5), ('screws', 4, 7)},
             'Mike'  : { ('pliers', 2, 5), ('screws', 4, 4), ('wrench', 3, 3) },
             'Katie' : { ('hammer', 1, 1), ('pliers', 2, 6), ('screws', 3, 5) } }
    
    print('\nTesting made_quota')
    print(made_quota(lexus))
    print(made_quota(ace))
    
    print('\nTesting sales1')
    print(sales1(lexus))
    print(sales1(ace))
    
    print('\nTesting sales2') 
    print(sales2(lexus))
    print(sales2(ace))
    print(sales2(ace2))
    
    print('\nTesting by_category')
    print(by_category(lexus))
    print(by_category(ace))

    print('\nTesting category_leader')
    print(category_leaders(lexus))
    print(category_leaders(ace))

    
    print('\ndriver testing with batch_self_check:')
    import driver
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()           





























