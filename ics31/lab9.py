#Shengquan Ni 46564157 and Erqiang Guo 58813913

from random import *
from collections import namedtuple
import tkinter



def create_text(root,text,x,y,anchor=tkinter.CENTER):
    text = tkinter.Label(root,text=text,anchor=None)
    text.place(x=x,y=y,anchor=anchor)


def stat_graph(l:'list student',total_score:int):
    my_window = tkinter.Tk()
    my_canvas = tkinter.Canvas(my_window, width=500, height=500)
    my_canvas.pack()
    #width: 400(50-450) 4
    #height: 300(100-400)
    heights=[0 for i in range(total_score+1)]
    total_student=len(l)
    for i in l:
        heights[i.total]+=1
    uplimit=max(heights)
    for i in range(len(heights)):
        heights[i]/=uplimit/300
    width_per_rect=400/total_score
    #x-axis and y-axis and arrows
    my_canvas.create_line(50,400,450,400)
    my_canvas.create_line(450,400,445,405)
    my_canvas.create_line(450,400,445,395)
    my_canvas.create_line(50,100,50,400)
    my_canvas.create_line(50,100,45,105)
    my_canvas.create_line(50,100,55,105)
    create_text(my_window,'Number of students',70,70)
    create_text(my_window,'Score',470,400)
    create_text(my_window,'0',40,405,tkinter.N)
    for i in range(5):
        create_text(my_window,str(int(uplimit*(i+1)/5)),45,400-300*(i+1)/5,tkinter.E)
    for i in range(10):
        create_text(my_window,str(int(total_score*(i+1)/10)),50-width_per_rect/2+400*(i+1)/10,405,tkinter.N)
    for i in range(total_score+1):
        if i<total_score-1:
            my_canvas.create_line(width_per_rect*(i+1)+50,397,width_per_rect*(i+1)+50,400)
        if heights[i]:
            my_canvas.create_rectangle(width_per_rect*(i+0.2)+50,400-heights[i],400/total_score*(i+0.8)+50,400,fill='black')
    my_window.mainloop()
        
'''
↑------optional-------↑

-------------------------

↓-------lab 9 --------↓
'''

NUMBER_OF_STUDENTS = 200
NUMBER_OF_QUESTIONS = 20
NUMBER_OF_CHOICES = 4

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
P('\n----------part(c.1)----------\n')

def generate_answers()->str:
    return ''.join([choice([chr(i+65)for i in range(NUMBER_OF_CHOICES)]) for j in range(NUMBER_OF_QUESTIONS)])

ANSWER=generate_answers()
P(ANSWER)

P('\n----------part(c.2-3)----------\n')

Student = namedtuple('Student', 'ID answers scores total')

def random_students()->list:
    result=[]
    for i in range(NUMBER_OF_STUDENTS):
        answer=generate_answers()          
        scores=[1 if answer[i]==ANSWER[i] else 0 for i in range(NUMBER_OF_QUESTIONS)]
        result.append(Student(''.join([str(randrange(0,10)) for i in range(8)]),answer,scores,sum(scores)))
    return result
                   
SL=random_students()
P(SL)
SL.sort(key=(lambda x:x.total),reverse=True)
P("TOP 10 students'ID:")
P([i.ID for i in SL[:10]])
P('Average Score: {:}'.format(sum([i.total for i in SL])/len(SL)))

stat_graph(SL,NUMBER_OF_QUESTIONS)

P('\n----------part(c.4)----------\n')

def generate_weighted_student_answer(s:str)->str:
    count=randrange(0,9)
    l=[chr(i+65)for i in range(4)]+[s for i in range(count)]
    return choice(l)

def random_students2()->list:
    result=[]
    for i in range(NUMBER_OF_STUDENTS):
        answer=''.join([generate_weighted_student_answer(ANSWER[i]) for i in range(NUMBER_OF_QUESTIONS)])          
        scores=[1 if answer[i]==ANSWER[i] else 0 for i in range(NUMBER_OF_QUESTIONS)]
        result.append(Student(''.join([str(randrange(0,10)) for i in range(8)]),answer,scores,sum(scores)))
    return result


SL2=random_students2()
P(SL2)
SL2.sort(key=(lambda x:x.total),reverse=True)
P("TOP 10 students'ID:")
P([i.ID for i in SL2[:10]])
P('Average Score: {:}'.format(sum([i.total for i in SL2])/len(SL2)))

stat_graph(SL2,NUMBER_OF_QUESTIONS)



P('\n----------part(c.5)----------\n')

def question_weights(l:list)->list:
    result=[0 for i in range(NUMBER_OF_QUESTIONS)]
    for i in l:
        for j in range(NUMBER_OF_QUESTIONS):
            if not i.scores[j]:
                result[j]+=1
    return result


def question_weights2(l:list)->list:
    result=[0 for i in range(NUMBER_OF_QUESTIONS)]
    for i in l:
        for j in range(NUMBER_OF_QUESTIONS):
            result[j]+=i.scores[j]
    return [weights(i/len(l)) for i in result]

def weights(f:float):
    if f>0.75:
        return 1
    elif f>0.5:
        return 2
    elif f>0.25:
        return 3
    else:
        return 4



WEIGHTS=question_weights2(SL2)
                
            
def Student_weighted_score(l:list,l2:list)->list:
    for i in range(len(l)):
        newscores=[l[i].scores[j]*l2[j] for j in range(NUMBER_OF_QUESTIONS)]
        l[i]=l[i]._replace(scores=newscores,total=sum(newscores))
    return l

SL2=Student_weighted_score(SL2,WEIGHTS)
P(SL2)
SL2.sort(key=(lambda x:x.total),reverse=True)
P("TOP 10 students' ID:")
P([i.ID for i in SL2[:10]])
P('Average Score: {:}'.format(sum([i.total for i in SL2])/len(SL2)))


stat_graph(SL2,sum(WEIGHTS))



P('\n----------part(d)----------\n')
P('\n----------part(d.1)----------\n')
P('\n----------part(d.1a)----------\n')


def calculate_GPA(l:list)->float:
    return sum([ord('E')-ord(i) if i!='F' else 0 for i in l])/len(l) if len(l) else 0

assert calculate_GPA(['A', 'C', 'A', 'B', 'A', 'F', 'D']) == 2.5714285714285716

P('\n----------part(d.1b)----------\n')

def calculate_GPA2(l:list)->float:
    total=0
    for i in l:
        if i.find('+')!=-1:
            i=i.replace('+','')
            total+=0.3
        elif i.find('-')!=-1:
            i=i.replace('-','')
            total-=0.3
        total+=ord('E')-ord(i) if i!='F' else 0
    return total/len(l)

assert calculate_GPA2(['A+', 'C+', 'A-', 'B-', 'A', 'F', 'D']) == 2.5714285714285716
        
P('\n----------part(d.2)----------\n')

def flatten_2D_list(l:list)->list:
    result=[]
    for i in l:
        result.extend(i)
    return result

assert flatten_2D_list([[1, 3, 2], [3, 5, 1], [7, 5, 1], [3, 2], [9, 4]]) == [1, 3, 2, 3, 5, 1, 7, 5, 1, 3, 2, 9, 4]

P('\n----------part(d.3)----------\n')
P('\n----------part(d.3a)----------\n')

def skip_every_third_item(l:list)->None:
    for i in range(len(l)):
        if i%3!=2:
            print(l[i])
    
P('\n----------part(d.3b)----------\n')

def skip_every_nth_item(l:list,num:int)->None:
    if num>0:
        for i in range(len(l)):
            if i%num!=num-1:
                print(l[i])

L = ['If', 'you', '432234', 'did', 'the', '9834234', 'exercise', 'correctly', '534523423', 
		 'this', 'should', '1044323', 'be', 'readable']

skip_every_third_item(L)
skip_every_nth_item(L,3)



P('\n----------part(d.4)----------\n')


work_week = ['Bob', 'Jane', 'Kyle', 'Larry', 'Brenda', 'Samantha', 'Bob', 
             'Kyle', 'Larry', 'Jane', 'Samantha', 'Jane', 'Jane', 'Kyle', 
             'Larry', 'Brenda', 'Samantha']


P('\n----------part(d.4a)----------\n')

def tally_days_worked(l:list):
    result={}
    for i in l:
        if result.get(i):
            result[i]+=1
        else:
            result[i]=1
    return result


workers=tally_days_worked(work_week)


P('\n----------part(d.4b)----------\n')

hourly_wages = {'Kyle': 13.50, 'Brenda': 8.50, 'Jane': 15.50, 'Bob': 30.00, 'Samantha': 8.50, 'Larry': 8.50, 'Huey': 18.00}


def pay_employees(d1:dict, d2:dict)->None:
    for k in d1.keys():
        print("{:} will be paid ${:.2f} for {:} hours of work at ${:.2f} per hour.".format(k,d1[k]*8*d2[k],d1[k]*8,d2[k]))

pay_employees(workers, hourly_wages)



P('\n----------part(d.5)----------\n')

def reverse_dict(d:dict)->dict:
    return {v:k for k,v in d.items()}




























