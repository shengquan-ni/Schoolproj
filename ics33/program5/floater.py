# A Floater is Prey; it updates by moving mostly in
#   a straight line, but with random changes to its
#   angle and speed, and displays as ufo.gif (whose
#   dimensions (width and height) are computed by
#   calling .width()/.height() on the PhotoImage


from PIL.ImageTk import PhotoImage
from PIL import Image
from prey import Prey
from random import random
import math

class Floater(Prey):
    def __init__(self,x,y):
        self._image=PhotoImage(file='ufo.gif')
        Prey.__init__(self,x,y,self._image.width(),self._image.height(),random()*math.pi*2,5)
    def update(self):
        if random()*100<30:
            self._angle+=random()-0.5
            self._speed+=random()-0.5
        elif random()<0.5:
            self._angle+=random()-0.5
        else:
            self._angle+=random()-0.5
        if self._speed<3:
            self._speed=3
        elif self._speed>7:
            self._speed=7
        self.move()
    def display(self,canvas):
        sw,sh=(int(i) for i in self.get_dimension())
        iw,ih=self._image.width(),self._image.height()
        if sw!=iw or sh!=ih:
            self._image = PhotoImage(Image.open('ufo.gif').resize((sw,sh), Image.ANTIALIAS))
        canvas.create_image(*self.get_location(),image=self._image)
