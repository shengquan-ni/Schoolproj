#  Shengquan Ni 46564157 and Yangguang He 50947171.  ICS 31 Lab sec 7.  Lab asst 3.

# preparations:
def P(argu=''):
    print("  "+str(argu))

def P_list(list):
    for i in list:
        print("  "+str(i))
    print()





#
#
# Part (c)
#
#

P('\n---------- Part (c) ----------\n')

import math

#
#Part(c.1)
#
def abbreviate(str:str)->str:
    "takes any string as input and return its first three characters"
    return str[:3]
assert abbreviate('January')=='Jan'
assert abbreviate('abrill')=='abr'

P('\n  -------- Part (c.1) --------\n')

P(abbreviate('test1'))

#
#Part(c.2)
#
def find_area_square(num:int)->int:
    ''' takes as input a number representing the length of one side of a square
        and returns the area of that square'''
    return num**2
assert find_area_square(1)==1
assert find_area_square(5)==25

P('\n  -------- Part (c.2) --------\n')


P(find_area_square(25))

#
#Part(c.3)
#
def find_area_circle(num:int)->int:
    ''' takes as its input the radius of a circle and returns the area of
        that circle'''
    return num**2*math.pi
assert find_area_circle(1) == 3.141592653589793
assert find_area_circle(5) == 78.53981633974483

P('\n  -------- Part (c.3) --------\n')

P(find_area_circle(100))
P(find_area_circle(325))

#
#Part(c.4)
#

import random

def print_even_numbers(list:list):
    ''' takes a list of integers as input and prints each even number
        on the list'''
    for i in list:
        if i % 2 == 0:
            P(i)

P('\n  -------- Part (c.4) --------\n')

print_even_numbers([random.randint(0,100)for i in range(20)])

#
#Part(c.5)
#

def calculate_shipping(num:int)->float:
    ''' takes one argument, the weight of a package to be shipped. It returns the price for shipping the package,
        calculated as follows:
        For anything under 2 pounds, the rate is $2.00.
        For packages of 2 pounds but under 10 pounds, the rate is $5.00.
        For packages of 10 pounds or more, the rate is $5.00 plus $1.50 per
        pound for each pound over 10.'''

    if num<2:
        return 2.00
    elif num<10:
        return 5.00
    else:
        return 5.00+1.50*(num-10)

assert calculate_shipping(0.5)==2.00
assert calculate_shipping(8)==5.00
assert calculate_shipping(13)==9.50

P('\n  -------- Part (c.5) --------\n')

P(calculate_shipping(234))

# preparations:

import tkinter

def tk_with_func(func,argu):
    my_window = tkinter.Tk()    # Create the graphics window
    my_canvas = tkinter.Canvas(my_window, width=500, height=500)  # Create a 500x500 canvas to draw on
    my_canvas.pack()            # Put the canvas into the window
    func(argu,my_canvas)
    tkinter.mainloop()          # Combine all the elements and display the window

#
#Part(c.6)
#
 
def create_square(argupack,canvas):
    try:
        canvas.create_rectangle(argupack[0],argupack[1],argupack[0]+argupack[2],argupack[1]+argupack[2],fill='#FFC1CB')
        P("creation completed")
    except Exception as e:
        P('Error: '+str(e))

P('\n  -------- Part (c.6) --------\n')

tk_with_func(create_square,(random.randint(50,300),random.randint(50,300),random.randint(10,200)))

#e.g: wrong arguements 
#tk_with_func(create_square,('abc','abc','cbd'))


#
#Part(c.7)
#

def create_circle(argupack,canvas):
    try:
        canvas.create_oval(argupack[0],argupack[1],argupack[0]+argupack[2],argupack[1]+argupack[2],fill='#FFC1CB')
        P("creation completed")
    except Exception as e:
        P('Error: '+str(e))

P('\n  -------- Part (c.7) --------\n')

tk_with_func(create_circle,(random.uniform(10,100),random.uniform(20,300),random.uniform(50,200)))

#
#
# Part (d)
#
#

P('\n---------- Part (d) ----------\n')


# preparations:

from collections import namedtuple     # If this line is in your file already, you don't need it again
Restaurant = namedtuple('Restaurant', 'name cuisine phone dish price')
# Restaurant attributes: name, kind of food served, phone number, best dish, price of that dish
RC = [
    Restaurant("Thai Dishes", "Thai", "334-4433", "Mee Krob", 12.50),
    Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50),
    Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50),
    Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50),
    Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50),
    Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50),
    Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) ]


#
#Part(d.1)
#

P('\n  -------- Part (d.1) --------\n')

def restaurant_price(argu:Restaurant)->int:
    '''takes one argument, a Restaurant,
       and returns the value of the price field of that Restaurant'''
    return argu.price
assert restaurant_price(RC[0])==12.50
assert restaurant_price(RC[3])==15.50
assert restaurant_price(RC[-1])==10.50

for i in RC:
    P(restaurant_price(i))

#
#Part(d.2)
#

P('\n  -------- Part (d.2) --------\n')

P_list(sorted(RC,key=restaurant_price))

#
#Part(d.3)
#

P('\n  -------- Part (d.3) --------\n')

def costliest(list:list)->str:
    '''takes a list of Restaurants as its argument
       and returns the name of the highest-priced restaurant on that list'''
    list.sort(key=restaurant_price)
    return list[-1].name

def create_list():
    ''' create a short list of Restaurants'''
    return [ Restaurant("Apple", "Thai", "334-1231", "Mee Krob", 19.99),
    Restaurant("Banana", "Japanese", "335-4433", "Natto Temaki", 100.01),
    Restaurant("Orange", "Italian", "355-4433", "Stracotto", 87.65),
    Restaurant("Grape", "Thai", "324-4433", "Paht Woon Sen", 0.01)]

P(costliest(create_list()))

#
#Part(d.4)
#

P('\n  -------- Part (d.4) --------\n')

newRC=create_list()
P("before calling costliest:")
P_list(newRC)
P("costliest returned:"+costliest(newRC)+"\n")
P("after calling costliest:")
P_list(newRC)
del newRC


def costliest2(list:list)->str:
    '''takes a list of Restaurants as its argument
       and returns the name of the highest-priced restaurant on that list'''
    return sorted(list,key=restaurant_price)[-1].name

newRC=create_list()
P("before calling costliest2:")
P_list(newRC)
P("costliest2 returned:"+costliest2(newRC)+"\n")
P("after calling costliest2:")
P_list(newRC)
del newRC

#
#
# Part (e)
#
#

P('\n---------- Part (e) ----------\n')

# preparations:
Book = namedtuple('Book', 'author title genre year price instock')
BSI=[Book('James','How to cook ducks','cookbook',1920,20.00,5),
     Book('Alan', 'How to cook tomatoes','cookbook',1950,18.78,4),
     Book('Nick','Sports makes life better','sport',1940,35.55,10),
     Book('John','Galaxy','Technology',1975,20.99,2),
     Book('Mike','A story about rabbit','novel',2010,19.99,20),
     Book('Obama','A story about fox','novel',2012,9.88,23)]

def print_something(list,key,specfickey=None,specficname=None):
    for i in list:
        if hasattr(i,key):
            if specfickey:
                if getattr(i,specfickey)==specficname:
                    P(getattr(i,key))
            else:
                P(getattr(i,key))
        else:
            P(str(type(i))+"instance has no attribute "+str(key))
            return 

#
#Part(e.1)
#

P('\n  -------- Part (e.1) --------\n')

print_something(BSI,'title')



#
#Part(e.2)
#

P('\n  -------- Part (e.2) --------\n')

print_something(sorted(BSI,key=lambda x:x.title),'title')



#
#Part(e.3)
#

P('\n  -------- Part (e.3) --------\n')

P('before:')
print_something(BSI,'price')
for i in range(len(BSI)):
    BSI[i]=BSI[i]._replace(price=BSI[i].price*1.1)
P()
P('after:')
print_something(BSI,'price')

#
#Part(e.4)
#

P('\n  -------- Part (e.4) --------\n')

print_something(BSI,'title','genre','Technology')

#
#Part(e.5)
#

def sum_of_books(list:list):
    sum=0
    for i in list:
        sum+=i.instock
    return sum



P('\n  -------- Part (e.5) --------\n')

before=[]
after=[]
for i in BSI:
    if i.year<2000:
        before.append(i)
    else:
        after.append(i)

if sum_of_books(before)>sum_of_books(after):
    P('More titles before 2000'+'('+str(sum_of_books(before))+' vs. '+str(sum_of_books(after))+')')
else:
    P('More titles 2000 or later'+'('+str(sum_of_books(after))+' vs. '+str(sum_of_books(before))+')')


#
#Part(e.6)
#

P('\n  -------- Part (e.6) --------\n')

def inventory_value(Book:Book)->int:
    '''takes a Book as its argument
       and returns the value of our inventory of that book'''
    return Book.price*Book.instock

def top_value(list:list)->Book:
    ''' takes a list of Books as its argument
        and returns the Book object (from the list)
        that has the highest-vaue inventory'''
    max=0
    for i in list:
        if inventory_value(i)>max:
            max=inventory_value(i)
            result=i
    return result

topbook=top_value(BSI)
P('The highest-value book is '+topbook.title+' by '+topbook.author+', at a value of $'+str(inventory_value(topbook)))



#
#
# Part (f)
#
#

P('\n---------- Part (f) ----------\n')


def draw_eye(argupack,canvas):
    import random
    import math
    lx=argupack[0]
    ly=argupack[1]
    rx=argupack[2]
    ry=argupack[3]
    canvas.create_oval(lx,ly,rx,ry)
    canvas.create_oval((rx-lx)*0.25+lx,ly,(rx-lx)*0.75+lx,ry)
    canvas.create_oval((rx-lx)*0.4+lx,(ry-ly)*0.3+ly,(rx-lx)*0.6+lx,(ry-ly)*0.7+ly,fill='black')
    for i in range(150):
        p=(i/150)*(random.random()/10)*360
        x1=-(rx-lx)*0.25*math.sin(p)
        y1=-(rx-lx)*0.25*math.cos(p)
        x2=-(rx-lx)*0.1*math.sin(p)
        y2=-(rx-lx)*0.1*math.cos(p)
        canvas.create_line((rx+lx)*0.5+x1,(ry+ly)*0.5+y1,(rx+lx)*0.5+x2,(ry+ly)*0.5+y2)
    tempx=0
    tempy=0
    for i in range(100):
        t=i/100
        if tempx==0 or tempy==0:
            tempx=bezier_curve((lx,(lx+rx)/2,rx),t)
            tempy=bezier_curve(((ly+ry)/2-30,ly-30,(ly+ry)/2-30),t)
        else:
            temp1=bezier_curve((lx,(lx+rx)/2,rx),t)
            temp2=bezier_curve(((ly+ry)/2-30,ly-30,(ly+ry)/2-30),t)
            canvas.create_line(tempx,tempy,temp1,temp2)
            tempx=temp1
            tempy=temp2
        if (i+10)%25==0:
            temp3=0
            temp4=0
            for j in range(100):
                k=j/100
                if temp3==0 or temp4==0:
                    temp3=bezier_curve((tempx,tempx-20,tempx-10),k)
                    temp4=bezier_curve((tempy,tempy-10,tempy-20),k)
                else:
                    temp5=bezier_curve((tempx,tempx-20,tempx-10),k)
                    temp6=bezier_curve((tempy,tempy-10,tempy-20),k)
                    canvas.create_line(temp3,temp4,temp5,temp6)
                    temp3=temp5
                    temp4=temp6
    

def draw_mouth(argupack,canvas):
    x1=argupack[0]
    x2=argupack[1]
    y=argupack[2]
    distance=argupack[3]
    points=[]
    temp=0
    switch={
        1:lambda x:-0.008*(x-x1)*(x-x2)+y+distance,
        2:lambda x:0.001*distance*(x-y-distance)*(x-y+distance)+x1,
        3:lambda x:-0.006*(x-x1)*(x-x2)+y-distance,
        4:lambda x:-0.001*distance*(x-y-distance)*(x-y+distance)+x2
        }
    for k in range(4):
        temp=0
        if k%2==0:
            for i in range(x1,x2):
                if temp==0:
                    temp=switch[k+1](i)
                else:
                    canvas.create_line(i-1,temp,i,switch[k+1](i))
                    temp=switch[k+1](i)
        else:
            for j in range(y-distance,y+distance):
                if temp==0:
                   temp=switch[k+1](j)
                else:
                    canvas.create_line(temp,j-1,switch[k+1](j),j)
                    temp=switch[k+1](j)


def bezier_curve(argupack1,t):
    result=0
    l=len(argupack1)-1
    for i in range(l+1):
        if i==0 or i==l:
            result+=((1-t)**(l-i))*argupack1[i]*(t**i)
        else:
            result+=((1-t)**(l-i))*l*argupack1[i]*(t**i)
    return result


def draw_nose(argupack,canvas):
    tempx=0
    tempy=0
    for i in range(200):
        #Bezier curve:
        t=i/200
        if tempx==0 and tempy==0:
            tempx=bezier_curve((argupack[0],argupack[2],argupack[4],argupack[6]),t)
            tempy=bezier_curve((argupack[1],argupack[3],argupack[5],argupack[7]),t)
        else:
            temp1=bezier_curve((argupack[0],argupack[2],argupack[4],argupack[6]),t)
            temp2=bezier_curve((argupack[1],argupack[3],argupack[5],argupack[7]),t)
            canvas.create_line(tempx,tempy,temp1,temp2)
            tempx=temp1
            tempy=temp2

def draw_face(argupack,canvas):
    for i in range(2):
        draw_eye(argupack[i],canvas)
    draw_mouth(argupack[2],canvas)
    draw_nose(argupack[3],canvas)
    P("creation completed")

P("Surprise comming in 3 secs")
import time
for i in range(3):
    P(3-i)
    time.sleep(1)
    
tk_with_func(draw_face,[(100,100,200,150),(300,100,400,150),(180,320,400,15),(250,150,240,280,150,310,280,320)])












    

