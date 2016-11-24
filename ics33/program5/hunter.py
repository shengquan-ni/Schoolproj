# A Hunter is both a Mobile_Simulton and Pulsator: it updates
#   like a Pulsator, but it moves (either in a straight line
#   or in pursuit of Prey) and displays as a Pulsator.


from pulsator import Pulsator
from mobilesimulton import Mobile_Simulton
from prey import Prey
from special import Special
import math
import random
import model

class Hunter(Pulsator,Mobile_Simulton):
    hunt_range=200
    def __init__(self,x,y):
        Pulsator.__init__(self,x,y)
        self._speed=5
        self._angle=random.random()*math.pi*2

    def update(self):
        temp=model.find(lambda x:self.distance(x.get_location())<Hunter.hunt_range if isinstance(x,Prey) or (isinstance(x,Special) and x.host) else False)
        if len(temp):
            target=sorted(list(temp),key=lambda x:self.distance(x.get_location()))[0]
            self._angle=math.atan2(target._y-self._y,target._x-self._x)
        self.move()
        return Pulsator.update(self)
            
            
            
        
