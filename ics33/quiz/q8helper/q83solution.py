from   bag import Bag
import unittest  # use unittest.TestCase
import random    # use random.shuffle,random.randint

#random.shuffle(alist) mutates its alist argument, to be a random permutation
#random.randint(1,10)  returns a random number in the range 1-10 inclusive


class Test_Bag(unittest.TestCase):
    def setUp(self):
        self.alist=['d','a','b','d','c','b','d']
        self.bag=Bag(self.alist)

    def testlen(self):
        random.shuffle(self.alist)
        size=7
        while size:
            self.bag.remove(self.alist[size-1])
            size-=1
            assert len(self.bag)==size
    def testunique(self):
        random.shuffle(self.alist)
        size=7
        while size:
            self.bag.remove(self.alist[size-1])
            size-=1
            assert len(set(i for i in self.bag))==self.bag.unique()

    def testcontains(self):
        assert all([i in self.bag for i in ['a','b','c','d']]) and not 'x' in self.bag

    def testcount(self):
        assert all(self.bag.count(i)==j for i,j in {'a':1,'b':2,'c':1,'d':3,'x':0}.items())
        random.shuffle(self.alist)
        size=7
        while size:
            self.bag.remove(self.alist[size-1])
            size-=1
            assert len(self.bag)==size

    def test__eq__(self):
        l=[random.randint(1,10) for i in range(1000)]
        first=Bag(l)
        random.shuffle(l)
        second=Bag(l)
        assert first==second
        first.remove(l[0])
        assert first!=second
            
    def testadd(self):
        l=[random.randint(1,10) for i in range(1000)]
        first=Bag(l)
        second=Bag([])
        random.shuffle(l)
        for i in l:
            second.add(i)
        assert first==second

    def testremove(self):
        l=[random.randint(1,10) for i in range(1000)]
        first=Bag(l)
        try:
            first.remove(42)
        except Exception as e:
            assert type(e)==ValueError
            second=Bag(l)
            random.shuffle(l)
            for i in l:
                second.add(i)
            for i in l:
                second.remove(i)
            assert first==second
                

                       
        
