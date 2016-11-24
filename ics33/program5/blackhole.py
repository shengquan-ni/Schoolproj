# A Black_Hole is a Simulton; it updates by removing
#   any Prey whose center is contained within its radius
#  (returning a set of all eaten simultons), and
#   displays as a black circle with a radius of 10
#   (width/height 20).
# Calling get_dimension for the width/height (for
#   containment and displaying) will facilitate
#   inheritance in Pulsator and Hunter

from simulton import Simulton
from prey import Prey
from special import Special
import model

class Black_Hole(Simulton):
    radius=10
    def __init__(self,x,y):
        Prey.__init__(self,x,y,Black_Hole.radius*2,Black_Hole.radius*2,0,0)
        
    def update(self):
        return model.find(lambda x:self.contains(x.get_location()) if isinstance(x,Prey) or (isinstance(x,Special) and x.host) else False)
    
    def contains(self,xy):
        return self.distance(xy)<Black_Hole.radius
    
    def display(self,canvas):
        w,h=self.get_dimension()
        canvas.create_oval(self._x-w/2, self._y-h/2,
                           self._x+w/2, self._y+h/2,
                           fill='black')

        
