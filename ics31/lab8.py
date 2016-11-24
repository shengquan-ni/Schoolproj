# Zinan Xu 20871816 and Shengquan Ni 46564157.  ICS 31 Lab sec 7.  Lab asst 8.
from collections import namedtuple

def P(argu=''):
    if not isinstance(argu,list):
        if not isinstance(argu,str):
            argu=str(argu)
        if "\n" in argu:
            argu=argu.replace("\n","\n    ")
        print("    "+argu)
    else:
        P_list(argu) if len(argu)!=0 else print("    empty list")
    
def P_list(list):
    for i in list:
        P(i)


P('\n----------part(c)----------\n')
P('\n----------part(c.1)----------\n')

Dish = namedtuple('Dish', 'name price calories')
def read_menu_with_count(filepath)->list:
    result=[]
    file=open(filepath)
    count=int(file.readline().replace('\n',''))
    if count:
        for i in range(count):
            fields=file.readline().replace('\n','').split('\t')
            result.append(Dish(fields[0],float(fields[1][1:]),float(fields[2])))
    return result
P('menu1:')
P(read_menu_with_count('menu1.txt'))
P('menu2:')
P(read_menu_with_count('menu2.txt'))

P('\n----------part(c.2)----------\n')


def read_menu(filepath)->list:
    result=[]
    file=open(filepath)
    for i in file:
        fields=i.replace('\n','').split('\t')
        result.append(Dish(fields[0],float(fields[1][1:]),float(fields[2])))
    return result

a=read_menu('menu3.txt')

P('\n----------part(c.3)----------\n')

def write_menu(l:list,filepath)->None:
    writefile=open(filepath,'w')
    writefile.write(str(len(l))+'\n')
    for i in l:
        s=''
        s+='{:}\t${:.2f}\t{:}\n'.format(*i)
        writefile.write(s)
    writefile.close()

write_menu(a,'menu4.txt')


P('\n----------part(d)----------\n')

Course = namedtuple('Course', 'dept num title instr units')
# Each field is a string except the number of units
ics31 = Course('ICS', '31', 'Intro to Programming', 'Kay', 4.0)
ics32 = Course('ICS', '32', 'Programming with Libraries', 'Thornton', 4.0)
wr39a = Course('Writing', '39A', 'Intro Composition', 'Alexander', 4.0)
wr39b = Course('Writing', '39B', 'Intermediate Composition', 'Gross', 4.0)
bio97 = Course('Biology', '97', 'Genetics', 'Smith', 4.0)
mgt1  = Course('Management', '1', 'Intro to Management', 'Jones', 2.0)
  
Student = namedtuple('Student', 'ID name level major studylist')
# All are strings except studylist, which is a list of Courses.
sW = Student('11223344', 'Anteater, Peter', 'FR', 'PSB', [ics31, wr39a, bio97, mgt1])
sX = Student('21223344', 'Anteater, Andrea', 'SO', 'CS', [ics31, wr39b, bio97, mgt1])
sY = Student('31223344', 'Programmer, Paul', 'FR', 'COG SCI', [ics32, wr39a, bio97])
sZ = Student('41223344', 'Programmer, Patsy', 'SR', 'PSB', [ics32, mgt1])
  
StudentBody = [sW, sX, sY, sZ]

P('\n----------part(d.1)----------\n')

def Students_at_level(l:list,s:str)->list:
    result=[]
    for i in l:
        if i.level==s:
            result.append(i)
    return result

P('\n----------part(d.2)----------\n')

def Students_in_majors(l1:list,l2:list)->list:
    result=[]
    for i in l1:
        if i.major in l2:
            result.append(i)
    return result

P('\n----------part(d.3)----------\n')

def Students_in_class(l1:list,dept:str,num:str)->list:
    result=[]
    for i in l1:
        if Student_is_enrolled(i,dept,num):
            result.append(i)
    return result

def Course_equals(c1: Course, c2: Course) -> bool:
    ''' Return True if the department and number of c1 match the department and
	     number of c2 (and False otherwise)
    '''
    return c1.dept==c2.dept and c1.num==c2.num

def Course_on_studylist(c: Course, SL: 'list of Course') -> bool:
    ''' Return True if the course c equals any course on the list SL (where equality
	     means matching department name and course number) and False otherwise.
    '''
    for i in SL:
        if Course_equals(c,i):
            return True
    return False

def Student_is_enrolled(S: Student, department: str, coursenum: str) -> bool:
    ''' Return True if the course (department and course number) is on the student's
	     studylist (and False otherwise)
    '''
    for i in S.studylist:
        if i.dept==department and i.num==coursenum:
            return True
    return False



P('\n----------part(d.4)----------\n')


def Student_names(l:list)->list:
    return [i.name for i in l]



P('\n----------part(d.5)----------\n')

def Students_average_units(l:list)->float:
    result=0
    for i in l:
        for j in i.studylist:
            result+=j.units
    return result/len(l) if len(l) else 0


P('\n----------part(d.5.1)----------\n')

L1=Students_in_majors(StudentBody, ['CS', 'CSE', 'BIM', 'INFX', 'CGS', 'SE', 'ICS'])
P(L1)
P('\n----------part(d.5.2)----------\n')

P(Student_names(L1))
P('\n----------part(d.5.3)----------\n')

P(len(L1))
P('\n----------part(d.5.4)----------\n')

L2=Students_at_level(L1,'SR')
P(Student_names(L2))
P('\n----------part(d.5.5)----------\n')

P(len(L2))
P('\n----------part(d.5.6)----------\n')

L3=Students_at_level(StudentBody, 'SR')
P(str(len(L2)*100/len(L3))+'%')
P('\n----------part(d.5.7)----------\n')

L4=Students_in_class(Students_at_level(L1,'FR'),'ICS','31')
P(len(L4))
P('\n----------part(d.5.8)----------\n')

P(Students_average_units(Students_in_class(Students_at_level(StudentBody,'FR'),'ICS','31')))












