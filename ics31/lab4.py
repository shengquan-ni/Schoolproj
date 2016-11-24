#Shengquan Ni 46564157 and Zhengyi Xu 68996560.  ICS 31 Lab sec 7.  Lab asst 4.
def P(argu):
    if not isinstance(argu,str):
        argu=str(argu)
    print("    "+argu)
    
def P_list(list):
    for i in list:
        P(i)
def P_list2(list):
    str1=str(list)
    str1=str1.replace(',',',\n    ')
    P(str1)

import re
from collections import namedtuple

P('\n----------part(c)----------\n')
P('\n    --------part(c.1)------\n')
#solution 1:
'''
def test_number(num:int,type:str)->bool:
    if type=='even':
        return not bool(num%2)
    elif type=='odd':
        return bool(num%2)
    elif type=='positive':
        return num>0
    elif type=='negative':
        return num<0
    else:
        return False
'''
#improved 3 lines' solution:

def test_number(num:int,type:str)->bool:
    '''takes as input a number and a string
       returns True if the number has the property
       indicated by the string, and False if it doesn't
    '''
    switch={'even':lambda x:not bool(x%2),'odd':lambda x:bool(x%2),'positive':lambda x:x>0,'negative':lambda x:x<0}
    return switch[type](num) if type in switch else False

assert test_number(16,'even')
assert not test_number(18,'odd')
assert not test_number(199,'negative')
assert test_number(200,'positive')

P('\n    --------part(c.2)------\n')
def display()->None:
    '''takes no parameters. It prompts the user to enter any word
       or phrase and then prints out every character in that phrase,
       one per line'''
    for i in input('    Enter a word: '):
        P(i)
display()
P('\n    --------part(c.3)------\n')
def square_list(list:list)->None:
    ''' takes a list of integers and prints out each integer squared.'''
    for i in list:
        P(i**2)
square_list([1,2,3,4,5,6,7,8,9])
P('\n    --------part(c.4)------\n')
def match_first_letter(str:str,list:list)->None:
    ''' takes a one-character string and a list of strings and prints all 
        the strings in the list that start with the specified character'''
    for i in list:
        if i[0]==str:
            P(i)
match_first_letter('a',['Apple','all','apple','banana'])
P('\n    --------part(c.5)------\n')
def match_area_code(list:list,list2:list)->None:
    ''' takes as a list of telephone area codes
        (three-digit strings) and a list of phone
        numbers in the form shown below. The function
        will print the phone numbers whose area code
        is on the list of area codes'''
    for i in list:
        for j in list2:
            if i==j[1:4]:
                P(j)

match_area_code(['123','456'],['(123)213-123','(456)123-123'])
P('\n    --------part(c.6)------\n')
def matching_area_codes(list:list,list2:list)->list:
    '''takes as a list of telephone area codes
       (three-digit strings) and a list of phone numbers
       returns a list of the matching numbers'''
    result=[]
    for i in list:
        for j in list2:
            if i==j[1:4]:
                result.append(j)
    return result
assert matching_area_codes(['883','949'],['(949)213-123','(456)123-123','(883)123-123'])==['(883)123-123', '(949)213-123']
assert matching_area_codes(['999','888'],['(123)213-123','(456)123-123'])==[]

P('\n----------part(c)----------\n')

P('\n    --------part(d.1)------\n')

def is_vowel(str:str)->bool:
    ''' takes a one-character-long string and returns True if that character is a vowel and False otherwise'''
    vowels=['a','e','i','o','u','A','E','I','O','U']
    for i in vowels:
        if str==i:
            return True
    return False
assert is_vowel('a') 
assert is_vowel('U')
assert not is_vowel('X')
assert not is_vowel('?')

P('\n    --------part(d.2)------\n')
def print_nonvowels(str:str)->None:
    '''takes a string and prints out all the characters
       in the string that are not vowels'''
    result=''
    for i in str:
        if not is_vowel(i):
            result+=i
    P(result)

print_nonvowels('cats and dogs')
P('\n    --------part(d.3)------\n')
def nonvowels(str:str)->str:
    '''takes a string and returns a string containing
       all the characters in the parameter string that are not vowels'''
    result=''
    for i in str:
        if not is_vowel(i):
            result+=i
    return result
assert nonvowels('aeiouzzzxxxccc!!!')=='zzzxxxccc!!!'
assert nonvowels('cccaaatttsss.,.,')=='ccctttsss.,.,'
P('\n    --------part(d.4)------\n')
def consonants(str:str)->str:
    ''' takes a string and returns a string containing all the
        letters in the parameter string that are not vowels'''
    string=''
    for i in str:
        if not is_vowel(i) and i.isalpha():
            string+=i
    return string
assert consonants('aeiouzzzxxxccc!!!')=='zzzxxxccc'
assert consonants('cccaaatttsss.,.,')=='ccctttsss'
P('\n    --------part(d.5)------\n')
def select_letters(str:str,str2:str)->str:
    '''takes two parameters, both strings, and returns a string.'''
    result=''
    if str=='v':
        for i in str2:
            if is_vowel(i):
                result+=i
    elif str=='c':
        result=consonants(str2)
    else:
        return ''
    return result
assert select_letters('c','aeiouqwppp')=='qwppp'
assert select_letters('v','aeiouqwppp')=='aeiou'
assert select_letters('asdf','asdf')==''

P('\n    --------part(d.6)------\n')
#solution 1:
def hide_vowels(str:str)->str:
    ''' takes a string and returns a string in which every vowel in the parameter
        is replaced with a hyphen ("-") and all other characters remain unchanged.'''
    str=re.sub('[aeiouAEIOU]', '-', str)
    return str
#solution 2:
'''
def hide_vowels(str:str)->str:
    result=''
    for i in str:
        if is_vowel(i):
           result+='-'
        else:
           result+=i
    return result
'''
#solution 3:
'''
def hide_vowels(str:str)->str:
    for i in str:
        if is_vowel(i):
            str=str.replace(i,'-')
    return str
'''
assert hide_vowels('monster')=='m-nst-r'
assert hide_vowels('APPLE')=='-PPL-'



P('\n----------part(e)----------\n')
Restaurant = namedtuple('Restaurant', 'name cuisine phone dish price')
# Restaurant attributes: name, kind of food served, phone number,
#	best dish, price of that dish

R1 = Restaurant("Taillevent", "French", "343-3434", "Escargots", 24.50)
R2 = Restaurant("La Tour D'Argent", "French", "343-3344", "Ris de Veau", 48.50)
R3 = Restaurant("Pascal", "French", "333-4444", "Bouillabaisse", 32.00)
R4 = Restaurant("Thai Touch", "Thai", "444-3333", "Mee Krob", 10.95)
R5 = Restaurant("Thai Dishes", "Thai", "333-4433", "Paht Woon Sen",  8.50)
R6 = Restaurant("Thai Spoon", "Thai", "334-3344", "Mussamun", 9.00)
R7 = Restaurant("McDonald's", "Burgers", "333-4443", "Big Mac", 3.95)
R8 = Restaurant("Burger King", "Burgers", "444-3344", "Whopper", 3.75)
R9 = Restaurant("Wahoo's", "Fish Tacos", "443-4443", "Mahi Mahi Burrito", 7.50)
R10 = Restaurant("In-N-Out Burger", "Burgers", "434-3344", "Cheeseburger", 2.50)
R11 = Restaurant("The Shack", "Burgers", "333-3334", "Hot Link Burger", 4.50)
R12 = Restaurant("Gina's", "Pizza", "334-4433", "Combo Pizza", 12.95)
R13 = Restaurant("Peacock, Room", "Indian", "333-4443", "Rogan Josh", 12.50)
R14 = Restaurant("Gaylord", "Indian", "333-3433", "Tandoori Chicken", 13.50)
R15 = Restaurant("Mr. Chow", "Chinese", "222-3333", "Peking Duck", 24.50)
R16 = Restaurant("Chez Panisse", "California", "222-3322", "Grilled Duck Breast", 25.00)
R17 = Restaurant("Spago", "California", "333-2222", "Striped Bass", 24.50)
R18 = Restaurant("Sriped Bass", "Seafood", "333-2233", "Cedar Plank Salmon", 21.50)
R19 = Restaurant("Golden Pagoda", "Chinese", "232-3232", "Egg Foo Young", 8.50)
R20 = Restaurant("Langer's", "Delicatessen", "333-2223", "Pastrami Sandwich", 11.50)
R21 = Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50)
R22 = Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50)
R23 = Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50)
R24 = Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50)
R25 = Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50)
R26 = Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) 


RL = [R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15, R16,
	R17, R18, R19, R20, R21, R22, R23, R24, R25, R26]

def Restaurant_change_price(r:Restaurant,num:'int/float')->Restaurant:
    ''' takes two arguments, a Restaurant object and a number, and returns
        a Restaurant object with the same contents as
        the parameter except that the price has been increased
        by the specified number.'''
    return r._replace(price=r.price+num)
r1=Restaurant('hello','food','123-456-789','fish',10)
P(Restaurant_change_price(r1,10))

P('\n----------part(f)----------\n')

P('\n    --------part(f.1)------\n')

def alphabetical(list:list)->list:
    '''takes a list of restaurants and
       returns that list in alphabetical order by name'''
    return sorted(list,key=lambda x:x.name)

P('RL[0] to RL[5] in alphabetical order by name:\n')
P_list(alphabetical(RL[:5]))

P('\n    --------part(f.2)------\n')

def alphabetical_names(list:list)->list:
    '''takes a list of restaurants and
       returns a list of the names of all the restaurants in alphabetical
       order by name.'''
    return sorted([i[0] for i in list])

P('a list of the names of RL[0] to RL[5] in alphabetical order by name:\n')
P_list(alphabetical_names(RL[:5]))

P('\n    --------part(f.3)------\n')

def all_Thai(list:list)->list:
    ''' takes a list of restaurants and returns a list of all the Thai restaurants '''
    return [i for i in list if i.cuisine=='Thai']

P('a list of all the Thai restaurants:\n')
P_list(all_Thai(RL))

P('\n    --------part(f.4)------\n')

def select_cuisine(list:list,type:str)->list:
    '''takes a list of restaurants and a string representing a cuisine.
       It should return a list of all the restaurants that serve the
       specified cuisine.'''
    return [i for i in list if i.cuisine==type]

P('a list of all the restaurants that serve Chinese cuisine:\n')
P_list(select_cuisine(RL,'Chinese'))

P('\n    --------part(f.5)------\n')

def select_cheaper(list:list,cost:float)->list:
    '''takes a list of restaurants and a number (a float) and
       returns a list of all the restaurants whose price is less than
       the specified number.'''
    return [i for i in list if i.price<cost]

P('a list of all the restaurants whose price is less than 5:\n')
P_list(select_cheaper(RL,5))

P('\n    --------part(f.6)------\n')

def average_price(list:list)->float:
    '''takes a list of restaurants and
       returns the average price of (the best dishes at) those restaurants'''
    sum=0
    for i in list:
        sum+=i.price
    return sum/len(list)

P('the average price of RL:\n')
P(average_price(RL))

P('\n    --------part(f.7)------\n')

P(average_price(select_cuisine(RL,'Indian')))

P('\n    --------part(f.8)------\n')

P(average_price(select_cuisine(RL,'Chinese')+all_Thai(RL)))

P('\n    --------part(f.9)------\n')

P_list2(alphabetical_names(select_cheaper(RL,15.00)))

P('\n----------part(g)----------\n')

import tkinter
import time
def tk_with_func(func,argu):
    my_window = tkinter.Tk()    # Create the graphics window
    my_canvas = tkinter.Canvas(my_window, width=500, height=500)  # Create a 500x500 canvas to draw on
    my_canvas.pack()            # Put the canvas into the window
    func(argu,my_canvas)
    tkinter.mainloop()          # Combine all the elements and display the window


def create_rectangle_from_center(argupack,canvas):
    '''takes four arguments: the x-value and y-value of the point in the center of the
       rectangle and the height and width of the rectangle
       then draw a rectangle'''
    center_x,center_y,height,width=argupack
    dx=1
    dy=1
    timecount=75
    rects=[]
    temprect=canvas.create_rectangle(center_x,center_y,center_x,center_y)
    while dx and dy:
        if timecount>0:
            timecount-=1
            canvas.delete(temprect)
            if(dx<width/2):
                dx*=1.5
            else:
                dx=width/2
            if(dy<height/2):
                dy*=1.5
            else:
                dy=height/2
            temprect=canvas.create_rectangle(center_x-dx,center_y-dy,center_x+dx,center_y+dy)
            if timecount==0:
                canvas.delete(temprect)
        else:
            for i in rects:
                canvas.delete(i)
            del rects[:]
            if(dx>1):
                dx/=1.2
            else:
                dx=0
            if(dy>1):
                dy/=1.2
            else:
                dy=0
            if dx!=0 and dy!=0:
                for i in range(3):
                    for j in range(3):
                        rects.append(canvas.create_rectangle(center_x+(width/3)*(i-1)+dx/2,center_y+(height/3)*(j-1)+dy/2,center_x+(width/3)*(i-1)-dx/2,center_y+(height/3)*(j-1)-dy/2))
        canvas.update()
        time.sleep(0.03)



P('Animation!!!!!!!it will burst a rectangle and split into 9 smaller rectangles and fade away after 2.25 sec')        
tk_with_func(create_rectangle_from_center,[250,250,250,250])






        

