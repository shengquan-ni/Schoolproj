#Shengquan Ni 46564157 Yingda Tao 59806566 ICS 31 Lab sec 7.  Lab asst 5.

import random
def P(argu=''):
    if not isinstance(argu,list):
        if not isinstance(argu,str):
            argu=str(argu)
        if "\n" in argu:
            argu=argu.replace("\n","\n    ")
        print("    "+argu)
    else:
        P_list(argu)
    
def P_list(list):
    for i in list:
        P(i)

from collections import namedtuple

Dish=namedtuple('Dish','name price cal')

P('\n----------part(c)----------\n')

P('\n    --------part(c.1)------\n')


d1=Dish('Fish',20.99,300.01)
d2=Dish('Ham',8.23,213.2314)
d3=Dish('Taco',9.12,456.000)

P('\n    --------part(c.2)------\n')

def Dish_str(dish:'Dish')->str:
     '''takes a Dish and returns a string in this form:
        Paht Woon Sen ($9.50): 330 cal'''
     return dish.name+" (${:.2f}".format(dish.price)+"): "+str(dish.cal)+" cal"

assert Dish_str(d1)=='Fish ($20.99): 300.01 cal'
assert Dish_str(d2)=='Ham ($8.23): 213.2314 cal'

P('\n    --------part(c.3)------\n')

def Dish_same(dish1:'Dish',dish2:'Dish')->bool:
    ''' takes two dishes as arguments 
        returns True if the names of the two dishes
        and their calorie counts are equal'''
    return dish1.name==dish2.name and dish1.cal==dish2.cal

assert not Dish_same(d1,d2)
assert not Dish_same(d2,d3)

P('\n    --------part(c.4)------\n')

def Dish_change_price(dish:'Dish',num:int)->'Dish':
    ''' takes a Dish and a number
        returns a Dish that's the same as the parameter except
        that its price is changed as follows:
        The number (positive or negative) represents a percentage
        change in price '''
    return dish._replace(price=dish.price*((100+num)/100))

P(Dish_change_price(d1,-10))
P(Dish_change_price(d2,50))
P(Dish_change_price(d3,100))
P(Dish_change_price(d1,-120))
P(Dish_change_price(d2,80))
P(Dish_change_price(d3,400))

P('\n    --------part(c.5)------\n')

def Dish_is_cheap(dish:'Dish',num:int)->bool:
    ''' takes a Dish and a number
        returns True if the Dish's price is less than that number'''
    return dish.price<num

assert Dish_is_cheap(d1,21)
assert not Dish_is_cheap(d2,8.23)

P('\n    --------part(c.6)------\n')

DL=[
    Dish('Beef',20,123),
    Dish('Pork',23,555),
    Dish('Chicken',12,233),
    Dish('Duck',0.1,256),
    Dish('Dumpling',1.11,2.22)]
DL.sort()
DL.append(Dish('Hamburger',1,1000))
P(DL)
DL2=[
    d1,
    d2,
    d3,
    Dish('Fish',100,1000)]
DL.extend(DL2)
P(DL)


def Dishlist_display(list:'list of Dish')->str:
    '''takes a list of Dishes and returns one large string consisting of
       the string representation of each dish followed by a newline ('\n') character'''
    result=''
    for i in list:
        result+=Dish_str(i)+"\n"
    return result

P(Dishlist_display(DL))

P('\n    --------part(c.7)------\n')

def Dishlist_all_cheap(list:'list of Dish',num:int)->bool:
    ''' takes a list of Dishes and a number
        returns True if the price of every dish on the list is less
        than that number'''
    for i in list:
        if not Dish_is_cheap(i,num):
            return False
    return True

assert Dishlist_all_cheap(DL,10000000)

P('\n    --------part(c.8)------\n')

def Dishlist_change_price(list:'list of Dish',num:int)->list:
    ''' takes a list of Dishes and a number representing a percentage change
        returns a list of Dishes with each price changed by the specified amount.'''
    for i in list:
       i=Dish_change_price(i,num)
    return list


P(Dishlist_change_price(DL,120))

P('\n    --------part(c.9)------\n')

def Dishlist_prices(list:'list of Dish')->list:
    '''takes a list of Dishes 
       returns a list of numbers containing just the prices
       of the dishes on that list'''
    return [i.price for i in list]

P(Dishlist_prices(DL))

P('\n    --------part(c.10)------\n')

def Dishlist_average(list:'list of Dish')->float:
    return sum(Dishlist_prices(list))/len(list) if len(list) else 0

P(Dishlist_average(DL))

P('\n    --------part(c.11)------\n')

def Dishlist_keep_cheap(list:'list of Dish',num:int)->list:
    ''' takes a list of Dishes and a number
        returns a list of those dishes on the original list that
        have prices less than that number'''
    return [i for i in list if Dish_is_cheap(i,num)]

P(Dishlist_keep_cheap(DL,10))

P('\n    --------part(c.12)------\n')


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



def Create_Dishes(list:'list of Resturants')->list:
    return [Dish(i.dish,i.price,random.randint(1,1000)) for i in list]


big_DL=Create_Dishes(RL)

P(big_DL)


def before_and_after()->None:
    '''It prompts the user for interactive input
       of a number representing a percentage change in prices;
       then it prints the result of Dishlist_display on your big list of Dishes;
       then it changes all the prices of the Dishes on the big list;
       then it prints the result of Dishlist_display again
       (reflecting the changed list of Dishes)'''
    num=float(input("    write a number representing a percentage change in prices: "))
    P(Dishlist_display(big_DL))
    P(Dishlist_display(Dishlist_change_price(big_DL,num)))

before_and_after()


P('\n----------part(e)----------\n')

P('\n    --------part(e.1)------\n')

Restaurant = namedtuple('Restaurant', 'name cuisine phone menu')
r1 = Restaurant('Thai Dishes', 'Thai', '334-4433', [Dish('Mee Krob', 12.50, 500),
                                                    Dish('Larb Gai', 11.00, 450)])
r2 = Restaurant('Taillevent', 'French', '01-44-95-15-01', 
				[Dish('Homard Bleu', 45.00, 750),
				 Dish('Tournedos Rossini', 65.00, 950),
				 Dish("Selle d'Agneau", 60.00, 850)])		
r3 = Restaurant('Pascal', 'French', '940-752-0107', 
				[Dish('escargots', 12.95, 250),
				 Dish('poached salmon', 18.50, 550),
				 Dish("rack of lamb", 24.00, 850),
                                 Dish('marjolaine cake',8.50,950)])	

P('\n    --------part(e.2)------\n')

def Restaurant_first_dish_name(R:Restaurant)->str:
    '''takes a Restaurant as its argument
       returns the name of the first dish on the restaurant's menu
    '''
    return R.menu[0].name if len(R.menu)>0 else ""

assert Restaurant_first_dish_name(r1)=='Mee Krob'
assert Restaurant_first_dish_name(r2)=='Homard Bleu'

P('\n    --------part(e.3)------\n')

def Restaurant_is_cheap(R:Restaurant,num:float)->bool:
    return Dishlist_average(R.menu)<=num
    
assert Restaurant_is_cheap(r1,12)
assert not Restaurant_is_cheap(r2,0)


P('\n    --------part(e.4)------\n')

C1=[r1,r2,r3]


def Restaurant_raise_prices(R:Restaurant,num:float)->None:
        Menu_raise_prices(R.menu,num)
        

def Menu_raise_prices(M:list,num:float)->None:
    for i in range(len(M)):
        M[i]=M[i]._replace(price=M[i].price+num)
        


def Collection_raise_prices(C:list,num:float)->None:
    for i in range(len(C)):
        Restaurant_raise_prices(C[i],num)
P('Before raising price by 10:\n')
P(C1)
P()
Collection_raise_prices(C1,10)
P('After raising price by 10:\n')
P(C1)
P()

def Collection_change_price(C:list,num:int)->None:
    for i in range(len(C)):
        Restaurant_change_prices(C[i],num)



def Restaurant_change_prices(R:Restaurant,num:float)->None:
        Menu_change_prices(R.menu,num)
        

def Menu_change_prices(M:list,num:float)->None:
    for i in range(len(M)):
        M[i]=M[i]._replace(price=M[i].price*((num+100)/100))
        
P('Before raising price by 100%:\n')
P(C1)
P()

Collection_change_price(C1,100)

P('After raising price by 100%:\n')
P(C1)
P()

P('\n    --------part(e.5)------\n')

def Collection_select_cheap(C:list,num:int)->list:
    result=[]
    for i in C:
        if Restaurant_is_cheap(i,num):
            result+=[i]
    return result

P("resaurants which's price below 50:\n")
P(Collection_select_cheap(C1,50))

P('\n----------part(g)----------\n')

Count=namedtuple('Count','letter number')
#previous solution:
'''
def letter_count(str1:str,str2:str)->list:
    start,result,str1,str2=0,[],str1.lower(),str2.lower()
    while start<len(str2):
        tempstr,count,substart=str2[start] if str2[start]!="\\" else  str2[start:start+2],0,0
        while substart<len(str1):
            if str1[substart:substart+len(tempstr)]==tempstr:
                count+=1
            substart+=len(tempstr)
        start+=len(tempstr)
        if not tempstr in [i.letter for i in result]:
            result.append(Count(tempstr,count))
    return result
'''
#improved solution:
def letter_count(str1:str,str2:str)->list:
    result=[]
    for i in str2:
        if not i in [i.letter for i in result]:
            result.append(Count(i,str1.count(i)))
    return result

P(letter_count("qewh1234598670876 54         3aASDFHGKFCCJYUF            GHDdfss\nxfkj\ndfhdf\nd","a      sdf\n\t"))
    
