#  Yicheng Zhu 40413601 and Shengquan Ni 46564157.  ICS 31 Lab sec 7.  Lab asst 7.
from random import randrange
import random
from collections import namedtuple

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

Name=namedtuple('Name','name,freq')

def Generator(filepath):
    result=[]
    file=open(filepath)
    text=file.readline()
    while text!='':
        temp=text.split()
        result.append(Name(*temp[:2]))
        text=file.readline()
    return result

surnames=Generator('surnames.txt')
mans=Generator('malenames.txt')
womans=Generator('femalenames.txt')

freq_sur=[float(i.freq) for i in surnames]
freq_man=[float(i.freq) for i in mans]
freq_woman=[float(i.freq) for i in womans]

def pick_freq(l:list):
    rnd = random.random()*sum(l)
    for i, w in enumerate(l):
        rnd -= w
        if rnd < 0:
            return i

def random_pick(l:list,l2:list)->str:    
    return l[pick_freq(l2)]

def random_names(n:int)->list:
    result=[]
    for i in range(n):
        s=random_pick(surnames,freq_sur).name.capitalize()+", "+(random_pick(mans,freq_man).name.capitalize() if randrange(0,2) else random_pick(womans,freq_woman).name.capitalize())
        result.append(s)
    return result

P(random_names(50))

P('\n----------part(d)----------\n')

def Caesar_break(s:str)->str:
    result=['' for i in range(26)]
    temp=s.split()
    length=len(temp)
    hit=[0 for i in range(26)]
    wordlist=open('wordlist.txt').read().split()
    for i in range(26):
        for j in temp:
            word=''
            for k in j:
                num=ord(k)
                if num>=97 and num<=122:
                    word+=chr(97+(num-97+i)%26)
                elif num>=65 and num<=90:
                    word+=chr(65+(num-65+i)%26)
                else:
                    if word in wordlist:
                        hit[i]+=1
                    word+=k
            result[i]+=word+' '
            if word in wordlist:
                hit[i]+=1
        if hit[i]==length:
            return result[i]
    max=0
    index=0
    for i in range(len(hit)):
        if max<hit[i]:
            max=hit[i]
            index=i
    return result[index]

ALPHABET='abcdefghijklmnopqrstuvwxyz'
def Caesar_encrypt(s:str,k:int)->str:
    return ''.join([ALPHABET[(ALPHABET.find(i)+k)%26] if i.isalpha() else i for i in s.lower()])

                  
P(Caesar_encrypt('hello, who!!! you!!! are!!!',23))
P(Caesar_break(Caesar_encrypt('hello, who!!! you!!! are!!!',23)))



P('\n----------part(e)----------\n')



def stats(l:list)->None:
    lines,emptylines,chars=0,0,0
    for s in l:
        lines+=len(s.split('\n'))
        for i in s.split('\n'):
            if not len(i.split()):
                emptylines+=1
        for i in s.split():
            chars+=len(i)
    return "{:6d}   lines in the list\n".format(lines)\
           +"{:6d}   empty lines\n".format(emptylines)\
           +"{:8.1f} average characters per line\n".format(chars/lines)\
           +"{:8.1f} average characters per non-empty line".format(chars/(lines-emptylines))

def copy_file():
    arg=input('    Please Enter a argument for copying: ')
    infile_name = input("    Please enter the name of the file to copy: ")
    infile = open(infile_name, 'r')
    outfile_name = input("    Please enter the name of the new copy:  ")
    outfile = open(outfile_name, 'w')
    num=0
    if arg=='Gutenberg trim':
        text=infile.read()
        start=text.find('*** START')
        end=text.rfind('*** END')
        start+=text[start:].find('\n')
        outfile.write(text[start:end])
    elif arg=='statistics':
        text=infile.read()
        outfile.write(text)
        s=stats([text])
        outfile.write(s)
        P(s)
    else:
        for line in infile:
            if arg=='line numbers':
                num+=1
                outfile.write('{:5d}: '.format(num)+line)
            else:
                outfile.write(line)
    infile.close()
    outfile.close()

copy_file()




                    
