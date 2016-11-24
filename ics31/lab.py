
from collections import namedtuple
Book=namedtuple('Book','title author year price')

def P(argu):
    print(argu)

def funcname1(length,partlen,partten):
    res=""
    while(len(res)+partlen<length):
              res+=partten;
    res+=partten[:length-len(res)]
    return res

def caln(n):
    if(n<=0):
        return 1
    else:
        return n*caln(n-1)

def sumeven(start,end):
    res=0
    while(start<=end):
        if(start %2==0):
            res+=start
        start+=1
    return res

def sumodd(start,end):
    res=0
    while(start<=end):
        if(start %2==1):
            res+=start
        start+=1
    return res

def average(group):
    res=0
    for i in group:
        res+=i
    res/=len(group)
    return res

def power(num,num2):
    count=1
    res=1
    while(count<=num2):
        res*=num
        count+=1
    return res

def kenticenergy(mess,velocity):
    return mess*velocity*velocity/2

def singlescore(group,index):
    return group[index-1]

def charmatch(string,start,end,char):
    if(start==end):
       return string[start-1]==char
    else:
       return string[start-1:end]==char

def makeword(words):
    s="abcdefghijklmnopqrstuvwxyz"
    end=len(words)
    res=""
    while(len(res)!=end):
        for i in s:
            if i==words[len(res)]:
                res+=i
                break
    return res




def lab2func():
    name=input('Hello, What is your name? ')
    print('Hello,',name,"!\nIt's nice to meet you")
    age=int(input('How old are you? '))
    print('Next year you will be',age+1,'years old\n Good-bye')
    

def lab2func2():
    name=input('Please provide this imformation\nBussiness name: ')
    euros=int(input('Number of euros: '))
    pounds=int(input('Number of pounds: '))
    dollars=int(input('Number of dollars: '))
    print('Copenhagen Chamber of Commerce\nBusiness name: '+name,'\n'
          +str(euros)+
          (' euros is 'if abs(euros)>1 else'euro is ')+str(7.46*euros),'krone\n'
          +str(pounds)+
          (' pounds is 'if abs(pounds)>1 else'pound is ')+str(10.33*pounds),'krone\n'
          +str(dollars)+
          (' dollars is 'if abs(dollars)>1 else'dollar is ')+str(6.66*dollars),'krone\n'
          ,'\nTotal krone:  ',7.46*euros+10.33*pounds+6.66*dollars
          )
    
def lab2func3():
    favorite = Book('Adventures of Sherlock Holmes','Arthur Conan Doyle', 1892, 21.50)
    another = Book('Memoirs of Sherlock Holmes', 'Arthur Conan Doyle', 1894, 23.50)
    still_another = Book('Return of Sherlock Holmes','Arthur Conan Doyle', 1905, 25.00)
    print(still_another.title)
    print(another.price)
    print((another.price+favorite.price+still_another.price)/3)
    print(favorite.year<1900)
    still_another._replace(price=26)
    still_another._replace(price=1.2*still_another.price)
    #lab2->g task
    booklist = [favorite, another, still_another]
    print(booklist[0].price<booklist[1].price)
    print(booklist[0].year>booklist[-1].year)
    

def lab2func4():
    Animal=namedtuple('Animal','name species age weight favoritefood')
    animals=[Animal('Jumbo','elephant',50,1000,'peanuts'),Animal('perry','platypus',7,1.7,'shrimp')]
    print(animals[0].weight<animals[1].weight)


def lab2func5():
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
    print(RC[2].name)
    print(RC[0].cuisine==RC[3].cuisine)
    print(RC[len(RC)-1].price)
    RC.sort()
    print(RC)
    print(RC[len(RC)-1].dish)
    RCnew=RC[:2]
    RCnew.extend(RC[-2:])
    print(RCnew)


def lab2_draw200rect(canvas):
    canvas.create_line(150,150,350,150,fill='blue')
    canvas.create_line(350,150,350,350,fill='blue')
    canvas.create_line(350,350,150,350,fill='blue')
    canvas.create_line(150,350,150,150,fill='blue')


def lab2_drawdiamond(canvas):
    canvas.create_line(200,150,300,150,fill='blue')
    canvas.create_line(200,150,150,225,fill='blue')
    canvas.create_line(300,150,350,225,fill='blue')
    canvas.create_line(150,225,350,225,fill='blue')
    canvas.create_line(150,225,250,350,fill='blue')
    canvas.create_line(350,225,250,350,fill='blue')
    canvas.create_line(300,150,250,350,fill='blue')
    canvas.create_line(200,150,250,350,fill='blue')
    
def lab2_drawhouse(canvas):
    canvas.create_polygon(250,200,175,250,325,250,fill='blue')
    canvas.create_rectangle(200,250,300,300)                     
    canvas.create_rectangle(230,275,270,300)
    canvas.create_oval(200,250,230,275)
    canvas.create_oval(270,250,300,275)




def lab2_draweye(canvas):
    import random
    import math
    canvas.create_oval(150,200,350,300)
    canvas.create_oval(200,200,300,300)
    canvas.create_oval(230,230,270,270,fill='black')
    for i in range(150):
        p=(i/150)*(random.random()/10)*360
        x1=-50*math.sin(p)
        y1=-50*math.cos(p)
        x2=-20*math.sin(p)
        y2=-20*math.cos(p)
        canvas.create_line(250+x1,250+y1,250+x2,250+y2)


def drawstar(canvas,centerx,centery,color,size):
    return canvas.create_oval(centerx-5-size,centery-5-size,centerx+5+size,centery+5+size,fill=color)



def fungalaxy(canvas):
    import random
    import math
    import time
    y=[]
    r=[]
    s=[]
    v=[1,3,4,2,7,6,5,4]
    color=['orange','white','blue','red','yellow','green','gray','blue']
    t=0
    trash=[]
    x1=235
    x2=265
    z=x1-300
    x1=x1*(170/(250-z))
    z=x2-300
    x2=x2*(170/(250-z))
    canvas.create_oval(x1,x1,x2,x2,fill='gold')
    for i in range(8):
        x1=230-20*i
        z=x1-300
        x1=x1*(170/(250-z))
        x2=270+20*i
        z=x2-300
        x2=x2*(170/(250-z))
        #canvas.create_oval(x1,x1,x2,x2)
        y.append(230-20*i)
        r.append(random.randint(0,360))
        s.append(2/(i+1))
    while(True):
        t+=0.1
        if t>360:
            t=0
        
        for i in range(8):
            x1=(y[i]-250)*math.sin(r[i]+t*s[i])+250
            y1=(y[i]-250)*math.cos(r[i]+t*s[i])+250
            z=x1-300
            x1=x1*(170/(250-z))
            y1=y1*(170/(250-z))
            vol=v[i]*(300/(250-z))
            trash.append(drawstar(canvas,x1,y1,color[i],vol))
        canvas.update()
        time.sleep(0.05)
        for i in trash:
            #end='trueend' in dir();
            #if end is False:
            canvas.delete(i)

def fungalaxy2(canvas):
    import random
    import math
    import time
    #import atexit
    #def onexit():
        #trueend=1
        #P('exit')
    #atexit.register(onexit)
    #canvas.create_oval(230,230,270,270)
    y=[]
    r=[]
    s=[]
    v=[1,3,4,2,7,6,5,4]
    color=['orange','white','blue','red','yellow','green','gray','blue']
    t=0
    trash=[]
    canvas.create_oval(240,240,260,260,fill='gold')
    for i in range(8):
        canvas.create_oval(230-20*i,230-20*i,270+20*i,270+20*i)
        y.append(230-20*i)
        r.append(random.randint(0,360))
        s.append(2/(i+1))
    while(True):
        t+=0.1
        if t>360:
            t=0
        for i in range(8):
            x1=(y[i]-250)*math.sin(r[i]+t*s[i])+250
            y1=(y[i]-250)*math.cos(r[i]+t*s[i])+250
            trash.append(drawstar(canvas,x1,y1,color[i],v[i]))
        canvas.update()
        time.sleep(0.05)
        for i in trash:
            canvas.delete(i)
            
        


def lab2func6(num):
    import tkinter
    my_window = tkinter.Tk()    # Create the graphics window
    my_canvas = tkinter.Canvas(my_window, width=500, height=500)  # Create a 500x500 canvas to draw on
    my_canvas.pack()# Put the canvas into the window
    switch={
    1:lambda x:lab2_draweye(x),
    2:lambda x:lab2_drawhouse(x),
    3:lambda x:lab2_draw200rect(x),
    4:lambda x:lab2_drawdiamond(x),
    5:lambda x:fungalaxy(x)# another vision: try "fungalaxy2(x)" instead! :P
    }
    switch[num](my_canvas)
    my_window.mainloop() # Combine all the elements and display the window

lab2func()
lab2func2()
lab2func3()
lab2func4()
lab2func5()
for i in range(5):
    lab2func6(i+1)






