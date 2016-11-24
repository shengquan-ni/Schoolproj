#Special(Simulation of the cell world)
#0.
#Special has genes, which is a sequance of 0(ineffective) and 1(effective), the genes' length is 24
#1.
#When Special was created, it will only carry 4 effective genes and it will infect the object which is a Prey instance
#When the object go into its infection range, it will pass its genes the object
#2.
#Every Special who has a host has its own genes, those genes decide the size, speed, lifespan of the host
#3.
#When a host "meet"(contains) another host(they must be the same type), they will reproduce,decrease their lifespan and their child will be created
#Their child's genes are the combination of their genes
#4.
#Every time genes get passed from one to another(e.g. reproduce, infect), it has 8% chance to mutate
#5.
#If a host's genes get some positions combination(e.g. position 1,4,17,19 are all 1), it's action will be different from its orginal form
#6.
#Host's color is determined by its genes
#7.
#If a host's lifespan equal to its counter, it will die and remove itself from the simulation


from simulton import Simulton
from prey import Prey
import random
import math
import model


def create_map():
    temp=[i+1 for i in range(24)]
    random.shuffle(temp)
    result={0:0}
    for i in range(6):
        for j in temp[i*4:(i+1)*4]:
            result[j]=i+1
    return result

def create_combos():
    result=[i for i in range(24)]
    random.shuffle(result)
    return [(result[i:i+4]) for i in range(6)]


     

class Special(Simulton):
    radius=3
    infection_time=50
    infection_range=15
    gene_number=24
    gene_types=6
    gene_mutate_chance=8
    color={0:'000000',1:'FF00FF',2:'FF0000',3:'00FF00',4:'FFFF00',5:'00FFFF',6:'0000FF'}
    map=create_map()
    combos=create_combos()
    def __init__(self,x,y,host=None,inher=0):
        self.host=host
        self.counter=0
        self.reproduce_counter=0
        self.reproduced=True
        self.lifespan=random.randrange(100,600)
        self.genes=inher if inher else self.generate_binary_num(4)
        self.effect_on_init()
        temp=self.count_1_bits(self.genes)
        if temp:
            self.color='#'+'{:0<6}'.format(hex(sum(int(Special.color[Special.map[((self.genes>>i)%2)*(i+1)]],16)//temp for i in range(Special.gene_number)))[2:])
        else:
            self.color='white'
        Simulton.__init__(self,x,y,Special.radius*2,Special.radius*2)

    def host_reproduce(self):
        temp=model.find(lambda x:self.host.contains(x.get_location()) if x!=self and ((isinstance(x,Special) and type(x.host)==type(self.host)) or isinstance(x,type(self.host))) else False)
        result=set()
        for i in temp:
            obj=None
            if isinstance(i,Special):
                if i.host and not i.reproduced:
                    h=type(i.host)(i._x,i._y) if random.randrange(0,2) else type(self.host)(i._x,i._y)
                    obj=Special(i._x,i._y,h,self.gene_reform(self.genes,i.genes))
                    i.reproduced=True
                    i.counter+=10
            else:
                obj=Special(i._x,i._y,i,self.gene_reform(self.genes))
                result.add(i)
            if obj:
                result.add((obj,'add'))
        return result

    
    def update(self):
        if self.host:
            if self.counter<self.lifespan:
                self.counter+=1
                self.host.update()
                self.effect_on_update()
                self.set_location(*self.host.get_location())
                if not self.reproduced:
                    result=self.host_reproduce()
                    if len(result)>0:
                        self.reproduced=True
                        self.counter+=40
                        return result
                elif self.reproduce_counter<=2**int(math.sqrt(len(model.object_pool))):
                    self.reproduce_counter+=1
                else:
                    self.reproduce_counter=0
                    self.reproduced=False
            else:
                return {self}
        else:
            if self.counter!=Special.infection_time:
                self.counter+=1
                return self.infect()
            else:
                return {self}
    
    def infect(self):
        location=self.get_location()
        temp=model.find(lambda x:x.distance(location)<Special.infection_range if x!=self and isinstance(x,Prey) else False)
        infected=set()
        for i in temp:
            if random.randrange(0,Special.infection_range)>=i.distance(location):
                infected.add(i)
                obj=Special(i._x,i._y,i,self.genes)
                infected.add((obj,'add'))
        return infected

    def gene_reform(self,gene1,gene2=0):
        if gene2:
            bp=random.randrange(0,24)
            result=(gene1>>bp<<bp)+gene2-(gene2>>bp<<bp)
        else:
            result=gene1
        for i in range(Special.gene_number):
            if random.randrange(0,100)<Special.gene_mutate_chance:
                result^=1<<i
        return result
                         
    def display(self,canvas):
        if self.host:
            self.host.display(canvas)
            canvas.create_oval(self.host._x-Special.radius, self.host._y-Special.radius,
                               self.host._x+Special.radius, self.host._y+Special.radius,
                               fill=self.color)
        else:
            canvas.create_oval(self._x-Special.infection_range, self._y-Special.infection_range,
                               self._x+Special.infection_range, self._y+Special.infection_range,
                               fill=self.color)

    def count_1_bits(self,num):
        count=0
        while num:
            count+=1
            num=num&(num-1)
        return count

    def generate_binary_num(self,num):
        l=[i for i in range(Special.gene_number)]
        result=0
        random.shuffle(l)
        for i in range(num):
            result|=1<<l[num]
        return result


    def effect_on_init(self):
        if self.host:
            for i in range(Special.gene_number):
                if (self.genes>>i)%2:
                    temp=Special.map[i+1]
                    if temp==1:
                        self.host.set_speed(self.host.get_speed()*1.2)
                    elif temp==2:
                        self.host.set_speed(self.host.get_speed()//1.2)
                    elif temp==5:
                        self.host.set_dimension(*(i*1.2 for i in self.host.get_dimension()))
                    elif temp==6:
                        self.host.set_dimension(*(i//1.2 for i in self.host.get_dimension()))
                    elif temp==3:
                        self.lifespan+=100
                    elif temp==4:
                        self.lifespan-=100



    def effect_on_update(self):
        if self.host:
            host=self.host
            l=[(self.genes>>i)%2 for i in range(24)]
            for i in range(len(Special.combos)):
                if all(l[j] for j in Special.combos[i]):
                    if i==0:
                        if not self.counter%50:
                            host._angle=random.random()*math.pi*2
                    elif i==1:
                        if not self.counter%25:
                            host._angle+=math.pi/2
                            if host._angle>math.pi*2:
                                host._angle-=math.pi
                    elif i==2:
                        if not self.counter%10:
                            host._speed*=0.98
                    elif i==3:
                        if not self.counter%10:
                            host._speed+=10
                        else:
                            host._speed*=0.88
