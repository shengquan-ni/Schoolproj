def compare(a,b):
   if len(a)==0 or len(b)==0:
      if len(a)>0:
         return '>'
      elif len(b)>0:
         return '<'
      else:
         return '='
   elif a[0]>b[0]:
      return '>'
   elif a[0]<b[0]:
      return '<'
   elif a[0]==b[0]:
      return compare(a[1:],b[1:])


def is_sorted(l):
   if len(l)<2:
      return True
   if len(l)==2:
      return l[0]<l[1]
   else:
      return is_sorted(l[1:]) and l[0]<l[1]
       


def merge (l1,l2):
   if len(l1)==0 or len(l2)==0:
      return l1 if len(l1)>len(l2) else l2
   return [l2[0]]+merge(l1,l2[1:]) if l1[0]>l2[0] else [l1[0]]+merge(l1[1:],l2)


def sort(l):
   if len(l)<2:
      return l
   elif len(l)==2:
      return [l[0],l[1]] if l[0]<l[1] else [l[1],l[0]]
   else:
      l1,l2=sort(l[:int(len(l)/2)]),sort(l[int(len(l)/2):])
      return merge(l1,l2)
      


def nested_sum(l):
   if len(l)==0:
      return 0
   elif type(l[0])==list:
      return nested_sum(l[0])+nested_sum(l[1:])
   else:
      return l[0]+nested_sum(l[1:])
      
        
        

if __name__=="__main__":
    import random,driver
    
    print('\nTesting compare')
    
    print(compare('',''))
    print(compare('','abc'))
    print(compare('abc',''))
    print(compare('abc','abc'))
    print(compare('bc','abc'))
    print(compare('abc','bc'))
    print(compare('aaaxc','aaabc'))
    print(compare('aaabc','aaaxc'))
   
    
    print('\nTesting is_sorted')
    print(is_sorted([]))
    print(is_sorted([1,2,3,4,5,6,7]))
    print(is_sorted([1,2,3,7,4,5,6]))
    print(is_sorted([1,2,3,4,5,6,5]))
    print(is_sorted([7,6,5,4,3,2,1]))
    
    print('\nTesting merge')
    print(merge([],[]))
    print(merge([],[1,2,3]))
    print(merge([1,2,3],[]))
    print(merge([1,2,3,4],[5,6,7,8]))
    print(merge([5,6,7,8],[1,2,3,4]))
    print(merge([1,3,5,7],[2,4,6,8]))
    print(merge([2,4,6,8],[1,3,5,7]))
    print(merge([1,2,5,7,10],[1,2,6,10,12]))


    print('\nTesting sort')
    print(sort([1,2,3,4,5,6,7]))
    print(sort([7,6,5,4,3,2,1]))
    print(sort([4,5,3,1,2,7,6]))
    print(sort([1,7,2,6,3,5,4]))
    l = list(range(20))  # List of values 0-19
    for i in range(10):  # Sort 10 times
        random.shuffle(l)
        print(sort(l),sep='-->')
    
    
    print('\nTesting nested_sum')
    print(nested_sum([1,2,3,4,5,6,7,8,9,10]))
    print(nested_sum([[1,2,3,4,5],[6,7,8,9,10]]))
    print(nested_sum([[1,[2,3],4,5],[[6,7,8],9,10]]))
    print(nested_sum([[1,[2,3],[[4]],5],[[6,[7,[8]]],[9,10]]]))


    print()
    driver.driver()
