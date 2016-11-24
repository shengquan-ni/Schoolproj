# David Brady 57424992 and Shengquan Ni 46564157 .ICS 31 Lab sec 7.  Lab asst 6.
from random import randrange

ALPHABET='abcdefghijklmnopqrstuvwxyz'

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

P('\n----------part(c)----------\n')

P('\n    --------part(c.1)------\n')

def contains(origin:str,cmp:str)->bool:
    return cmp in origin

assert contains('banana', 'ana')
assert not contains('racecar', 'ck')
assert contains('apple','app')
assert not contains('race','rc')


P('\n    --------part(c.2)------\n')


def sentence_stats(s:str)->None:
    table=s.maketrans("~@#$%^&*()!<>/\][{}`?,.:'=-+_",' '*len("~@#$%^&*()!<>/\][{}`?,.:'=-+_"))
    print('Characters: '+str(len(s))+'\nWords: '+str(len(s.translate(table).split()))+'\nAverage word length: '+str(sum([len(i) for i in s.translate(table).split()])/len(s.translate(table).split())))

sentence_stats('akjhdjah ahskjdakj    asdkja hakjsdhkjad kjhkjahds  jsalkd')
sentence_stats('213182 7198237981 ???? !!! !!! !!!   !!! iosad   ')
sentence_stats('I love UCI')
sentence_stats('***The ?! quick brown fox:  jumps over the lazy dog.')

P('\n    --------part(c.3)------\n')

def initials(s:str)->str:
    s=s.split()
    result=''
    for i in s:
        result+=i[0]
    return result.upper()

assert initials('Bill Cosby') == 'BC'
assert initials('Guido van Rossum') == 'GVR'
assert initials('alan turing') == 'AT'


P('\n----------part(d)----------\n')

P('\n    --------part(d.1)------\n')



def random_stuff(min:int,max:int)->None:
    for i in range(50):
        P(randrange(min,max))

random_stuff(0,11)
random_stuff(1,7)

P('\n    --------part(d.2)------\n')
def roll2dice()->int:
    return randrange(1,7)+randrange(1,7)

for i in range(50):
    P(roll2dice())

P('\n    --------part(d.3)------\n')
def distribution_of_rolls(num:int)->None:
    result=[0 for i in range(11)]
    for i in range(num):
        result[roll2dice()-2]+=1
    P('Distribution of dice rolls\n')
    for i in range(len(result)):
        P('{:2d}:{:6d} ({:4.1f}%)  '.format(i+2,result[i],result[i]*100/num)+'*'*result[i])
    P('-----------------------------')
    P('      {:d} rolls'.format(num))
        

distribution_of_rolls(100)
distribution_of_rolls(50)
distribution_of_rolls(25)

P('\n----------part(e)----------\n')

P('\n    ------part(e.1+e.3)----\n')
'''
def Caesar_encrypt(s:str,k:int)->str:
    result=''
    s=s.lower()
    for i in s:
        if i.isalpha():
            pos=ALPHABET.find(i)
            result+=ALPHABET[(pos+k)%26]
        else:
            result+=i
    return result
'''
def Caesar_encrypt(s:str,k:int)->str:
    return ''.join([ALPHABET[(ALPHABET.find(i)+k)%26] if i.isalpha() else i for i in s.lower()])

P(Caesar_encrypt('apple',27))

'''
def Caesar_decrypt(s:str,k:int)->str:
    result=''
    s=s.lower()
    for i in s:
        if i.isalpha():
            pos=ALPHABET.find(i)
            result+=ALPHABET[(pos-k)%26]
        else:
            result+=i
    return result
'''
def Caesar_decrypt(s:str,k:int)->str:
    return ''.join([ALPHABET[(ALPHABET.find(i)-k)%26] if i.isalpha() else i for i in s.lower()])

P(Caesar_decrypt(Caesar_encrypt('apple is gooood!!!!!!',5),5))


P('\n----------part(f)----------\n')

P('\n    --------part(f.1)------\n')

def print_line_numbers(l:list)->None:
    for i in range(len(l)):
        P('{:d}:  '.format(i+1)[:4]+l[i])

s=[ "Four score and seven years ago, our fathers brought forth on",
  "this continent a new nation, conceived in liberty and dedicated",
  "to the proposition that all men are created equal.\n  Now we are",
  "   engaged in a great 		civil war, testing whether that nation, or any",
  "nation so conceived and so dedicated, can long endure.       ",'aaaaaaaaaaaa','aaaaaaaaaaaa','aaaa','aaaa','aaaaa','aaaaa','aaaaa','aaaaa','aaaaaa','aaaaaa','aaaaaaa','sssss','ssssss','ssss','ssssss','sssss' ]
print_line_numbers(s)


P('\n    --------part(f.2)------\n')
s1=[
    '''(f) Suppose you have a list of strings containing English text, like this:
[ "Four score and seven years ago, our fathers brought forth on",
  "this continent a new nation, conceived in liberty and dedicated",
  "to the proposition that all men are created equal.  Now we are",
  "   engaged in a great civil war, testing whether that nation, or any",
  "nation so conceived and so dedicated, can long endure.        " ]
There might be additional spacing or punctuation, as shown in the last two lines above.
(f.1) Write the function print_line_numbers that takes a list of strings and prints each string preceded by a line number:
1:  Four score and seven years ago, our fathers brought forth on
2:  this continent a new nation, conceived in liberty and dedicated
3:  to the proposition that all men are created equal.  Now we are
4:     engaged in a great 		civil war, testing whether that nation, or any
5:  nation so conceived and so dedicated, can long endure.
If there are 10 lines or more, the text won't line up nicely. Use the format method to print each line number in a five-character-wide field. (A nifty enhancement would be to make the line number field width exactly as long as it has to be to display the longest line number.)
(f.2) Write the function stats that takes a list of strings and prints statistics as follows:
 16824   lines in the list
   483   empty lines
    53.7 average characters per line
    65.9 average characters per non-empty line
Follow the formatting shown.
(f.3) Write the function list_of_words that takes a list of strings as above and returns a list of individual words with all white space and punctuation removed (except for apostrophes/single quotes).
Look at the string operations and list operations to determine which of them you'll need for this task.''']



s2=[ "            Four score and seven years ago, our fathers brought forth on",
  "this continent a new nation, conceived in liberty and dedicated",
  "to the proposition that all men are created equal.  Now we are",
  "   engaged in a great 		civil war, testing whether that nation, or any",
     '               ',
     '',
  "nation so conceived and so dedicated, can long endure.        " ]





def stats(l:list)->None:
    lines,emptylines,chars=0,0,0
    for s in l:
        lines+=len(s.split('\n'))
        for i in s.split('\n'):
            if not len(i.split()):
                emptylines+=1
            else:
                chars+=len(i.strip())
    P( "{:6d}   lines in the list\n".format(lines)
      +"{:6d}   empty lines\n".format(emptylines)
      +"{:8.1f} average characters per line\n".format(chars/lines)
      +"{:8.1f} average characters per non-empty line".format(chars/(lines-emptylines)))

stats(s2)

P('\n    --------part(f.3)------\n')

def list_of_words(l:list)->list:
    words=[]
    for s in l:
        table=s.maketrans(''',.?!;:"[](){}_-<>''',' '*len(''',.?!;:"[](){}_-<>'''))
        words.extend(s.translate(table).split())
    return words
        
P(list_of_words(s1))        












        












