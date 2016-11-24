# Submitter: shenqgun(Shengquan, Ni)
# Partner  : changchs(Changchuan, Shen)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
from collections import defaultdict
from goody import type_as_str

class Bag:
    def __init__(self,data=None):
        self.data=defaultdict(int) if not data else {i:data.count(i) for i in data}

    def __repr__(self):
        return 'Bag('+str(sum(([i for j in range(self.data[i])] for i in self.data),[]))+')'

    def __str__(self):
        return 'Bag('+''.join('{}[{}]'.format(i,self.data[i]) for i in self.data)+')'

    def __len__(self):
        return sum(self.data[i] for i in self.data)

    def unique(self):
        return len(self.data.keys())

    def __contains__(self,arg):
        return arg in self.data

    def count(self,arg):
        return 0 if not arg in self.data else self.data[arg]

    def add(self,arg):
        self.data[arg]+=1

    def __add__(self,arg):
        if type(self)!=type(arg): raise TypeError
        return Bag(sum(([i for j in range(self.data[i])] for i in self.data),[])+sum(([i for j in range(arg.data[i])] for i in arg.data),[]))

    def remove(self,arg):
        if not arg in self.data:raise ValueError('{} is not exist in the bag'.format(arg))
        elif self.data[arg]>1:self.data[arg]-=1
        else: self.data.pop(arg)

    def __eq__(self,arg):
        return False if type(self)!=type(arg) else self.data==arg.data

    def __ne__(self,arg):
        return True if type(self)!=type(arg) else self.data!=arg.data

    def __iter__(self):
        return iter(sum(([i for j in range(self.data[i])] for i in self.data),[]))

    
    
        





if __name__ == '__main__':
    # You can put your own code to test Bags here
    print()
    import driver
    driver.default_file_name = 'bsc1.txt'
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
#     driver.default_show_traceback = True
    driver.driver()
