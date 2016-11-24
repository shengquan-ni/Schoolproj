# A Ball is Prey; it updates by moving in a straight
#   line and displays as blue circle with a radius
#   of 5 (width/height 10).


from prey import Prey
import random
import math

class Ball(Prey):
    radius=5
    def __init__(self,x,y):
        Prey.__init__(self,x,y,Ball.radius*2,Ball.radius*2,random.random()*math.pi*2,5)
    def update(self):
        self.move()
    def display(self,canvas):
        h,w=self.get_dimension()
        canvas.create_oval(self._x-w/2, self._y-h/2,
                           self._x+w/2, self._y+h/2,
                           fill='blue')
        
