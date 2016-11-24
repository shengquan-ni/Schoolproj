import prompt
from goody import irange


# List Node class and helper functions (to set up problem)

class LN:
    def __init__(self,value,next=None):
        self.value = value
        self.next  = next

def list_to_ll(l):
    if l == []:
        return None
    front = rear = LN(l[0])
    for v in l[1:]:
        rear.next = LN(v)
        rear = rear.next
    return front

def str_ll(ll):
    answer = ''
    while ll != None:
        answer += str(ll.value)+'->'
        ll = ll.next
    return answer + 'None'



# Tree Node class and helper functions (to set up problem)

class TN:
    def __init__(self,value,left=None,right=None):
        self.value = value
        self.left  = left
        self.right = right

def height(atree):
    if atree == None:
        return -1
    else:
        return 1+ max(height(atree.left),height(atree.right))

def size(t):
    if t == None:
        return 0
    else:
        return 1 + size(t.left) + size(t.right)
    
def is_balanced(t):
    if t == None:
        return True
    else:
        return abs(size(t.left)-size(t.right)) <= 1 and is_balanced(t.left) and is_balanced(t.right)
    
def str_tree(atree,indent_char ='.',indent_delta=2):
    def str_tree_1(indent,atree):
        if atree == None:
            return ''
        else:
            answer = ''
            answer += str_tree_1(indent+indent_delta,atree.right)
            answer += indent*indent_char+str(atree.value)+'\n'
            answer += str_tree_1(indent+indent_delta,atree.left)
            return answer
    return str_tree_1(0,atree) 



# Define copy_dropping ITERATIVELY

def copy_dropping(ll,value):
    result,temp=None,None
    while ll:
        if ll.value!=value:
            if not result:
                result=LN(ll.value)
                temp=result
            else:
                temp.next=LN(ll.value)
                temp=temp.next
        ll=ll.next
    return result


# Define copy_dropping_r RECURSIVELY

def copy_dropping_r(ll,value):
    if ll:
        if ll.value!=value:
            return LN(ll.value,copy_dropping_r(ll.next,value))
        else:
            return copy_dropping_r(ll.next,value)
            



# Define build_balanced_bst RECURSIVELY

def build_balanced_bst(l):
    if len(l)>1:
        return TN(l[int(len(l)/2)],build_balanced_bst(l[:int(len(l)/2)]),build_balanced_bst(l[int(len(l)/2)+1:]))
    elif len(l)==1:
        return TN(l[0])
    else:
        return None


# Define the derived StringVar_WithHistory using the StringVar base class
#   defined in tkinter

from tkinter import StringVar

class StringVar_WithHistory(StringVar):
    def __init__(self):
        self.history=[]
        StringVar.__init__(self)

    def set(self,value):
        if value!=self.get():
            self.history+=[value]
            StringVar.set(self,value)
    def undo(self):
        if len(self.history)>1:
            self.history=self.history[:-1]
            StringVar.set(self,self.history[-1])
            
# OptionMenuUndo: acts like an OptionMenu, but also allows undoing the most recently
#   selected option, all the way back to the title (whose selection cannot be undone).
# It overrides the __init__ method and defines the new methods get, undo, and 
#   simulate_selections.
# It will work correctly if StringVar_WithHistory is defined correctly
from tkinter import OptionMenu
class OptionMenuUndo(OptionMenu):
    def __init__(self,parent,title,*option_tuple,**configs):
        self.result = StringVar_WithHistory()
        self.result.set(title)
        OptionMenu.__init__(self,parent,self.result,*option_tuple,**configs)

    # Get the current option  
    def get(self):                
        return self.result.get() # Call get on the StringVar_WithHistory attribute

    # Undo the most recent option
    def undo(self):
        self.result.undo()       # Call undo on the StringVar_WithHistory attribute
      
    # Simulate selecting an option (mostly for test purposes)
    def simulate_selection(self,option):
        self.result.set(option)  # Call set on the StringVar_WithHistory attribute


# Testing Script
if __name__ == '__main__':
    
    print('Testing copy_dropping')
    ll = list_to_ll([1,8,2,4,2,5,2])
    answer   = copy_dropping(ll,2)
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(answer))
    print('original list (unmutated)  = ',str_ll(ll))
    
    ll = list_to_ll([2,2,1,8,2,4,2,5,2])
    answer   = copy_dropping(ll,2)
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(answer))
    print('original list (unmutated)  = ',str_ll(ll))

    ll = list_to_ll([2,2])
    answer   = copy_dropping(ll,2)
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(answer))
    print('original list (unmutated)  = ',str_ll(ll))

    # Put in your own tests here


    print('\nTesting copy_dropping_r')
    ll = list_to_ll([1,8,2,4,2,5,2])
    answer   = copy_dropping_r(ll,2)
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(answer))
    print('original list (unmutated)  = ',str_ll(ll))
    
    ll = list_to_ll([2,2,1,8,2,4,2,5,2])
    answer   = copy_dropping_r(ll,2)
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(answer))
    print('original list (unmutated)  = ',str_ll(ll))

    ll = list_to_ll([2,2])
    answer   = copy_dropping_r(ll,2)
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(answer))
    print('original list (unmutated)  = ',str_ll(ll))

    # Put in your own tests here


    print('\nTesting build_balanced')
    l = []
    print('\nfor values = ',l)
    t = build_balanced_bst(l)
    print('Height =',height(t))
    print('Tree is\n',str_tree(t),sep='')
          
    l = [i for i in irange(1,10)]
    print('\nfor values = ',l)
    t = build_balanced_bst(l)
    print('is_balanced =',is_balanced(t))
    print('Height =',height(t))
    print('Tree is\n',str_tree(t),sep='')
          
    l = [i for i in irange(1,20)]
    print('\nfor values = ',l)
    t = build_balanced_bst(l)
    print('is_balanced =',is_balanced(t))
    print('Height =',height(t))
    print('Tree is\n',str_tree(t),sep='')
    
    l = [i for i in irange(1,1024)]
    print('\nfor values from 1 to 1,024')
    t = build_balanced_bst(l)
    print('is_balanced =',is_balanced(t))
    print('Height =',height(t))
    # Tree is too big to print/read
          
  

    print('\nTesting OptionMenuUndo')
    from tkinter import *
    print('Simulate using StringVar_WithHistory or build/test actual GUI')
    if prompt.for_bool('Simulate',default=True):
        # Needed for obscure reasons
        root = Tk()
        root.title('Widget Tester')
        main = Frame(root)
        
        # Construct an OptionMenuUndo object for simulation
        omu = OptionMenuUndo(main, 'Choose Option', 'option1','option2','option3')
        
        # Initially its value is 'Choose Option'
        print(omu.get(), '   should be Choose Option')
        
        # Select a new option
        omu.simulate_selection('option1')
        print(omu.get(), '         should be option1')
        
        # Select a new option
        omu.simulate_selection('option2')
        print(omu.get(), '         should be option2')
        
        # Select the same option (does nothing)
        omu.simulate_selection('option2')
        print(omu.get(), '         should still be option2')
        
        # Select a new option
        omu.simulate_selection('option3')
        print(omu.get(), '         should be option3')
         
        # Undo the last option: from 'option3' -> 'option2'
        omu.undo()
        print(omu.get(), '         should go back to option2')
         
        # Undo the last option: from 'option2' -> 'option1'
        omu.undo()
        print(omu.get(), '         should go back to option1')
         
        # Undo the last option: from 'option1' -> 'Choose Option'
        omu.undo()
        print(omu.get(), '   should go back to Choose Option')
         
        # Cannot undo the first option: does nothing
        omu.undo()
        print(omu.get(), '   should still be Choose Option')

         
        # Cannot undo the first option: does nothing
        omu.undo()
        print(omu.get(), '   should still be Choose Option')
        
    else: #Build/Test real widget

        # #OptionMenuToEntry: with title, linked_entry, and option_tuple
        # #get is an inherited pull function; put is a push function, pushing
        # #  the selected option into the linked_entry (replacing what is there)
        # 
        root = Tk()
        root.title('Widget Tester')
        main = Frame(root)
        main.pack(side=TOP,anchor=W)
         
        omu = OptionMenuUndo(main, 'Choose Option', 'option1','option2','option3')
        omu.grid(row=1,column=1)
        omu.config(width = 10)
         
        b = Button(main,text='Undo Option',command=omu.undo)
        b.grid(row=1,column=2)
         
        root.mainloop()
