# A Pulsator is a Black_Hole; it updates as a Black_Hole
#   does, but also by growing/shrinking depending on
#   whether or not it eats Prey (and removing itself from
#   the simulation if its dimension becomes 0), and displays
#   as a Black_Hole but with varying dimensions


from blackhole import Black_Hole


class Pulsator(Black_Hole):
    counter=30
    def __init__(self,x,y):
        self.count=0
        Black_Hole.__init__(self,x,y)
    def update(self):
        result=Black_Hole.update(self)
        delta=len(result)
        if delta:
            self.change_dimension(delta,delta)
            self.count=0
        elif self.count!=Pulsator.counter:
            self.count+=1
        else:
            self.change_dimension(-1,-1)
            self.count=0
        if self.get_dimension()==(0,0):
            return {self}
        else:
            return result
    
