import controller, sys
import model   #strange, but we need a reference to this module to pass this module to update

from ball      import Ball
from floater   import Floater
from blackhole import Black_Hole
from pulsator  import Pulsator
from hunter    import Hunter
from special   import Special

# Global variables: declare them global in functions that assign to them: e.g., ... = or +=
running     = False
cycle_count = 0
object_pool = set()
now_select  = None

#return a 2-tuple of the width and height of the canvas (defined in the controller)
def world():
    return (controller.the_canvas.winfo_width(),controller.the_canvas.winfo_height())

#reset all module variables to represent an empty/stopped simulation
def reset ():
    global running,cycle_count,object_pool
    running     = False
    cycle_count = 0
    object_pool = set()


#start running the simulation
def start ():
    global running
    running=True

#stop running the simulation (freezing it)
def stop ():
    global running
    running=False 


#step just 1 update in the simulation
def step ():
    global running
    running=True
    update_all()
    display_all()
    running=False


#remember the kind of object to add to the simulation when an (x,y) coordinate in the canvas
#  is clicked next (or remember to remove an object by such a click)   
def select_object(kind):
    global now_select
    if kind !='Remove':
        now_select=eval(kind)
    else:
        now_select=kind


#add the kind of remembered object to the simulation (or remove any objects that contain the
#  clicked (x,y) coordinate
def mouse_click(x,y):
    global now_select,object_pool
    if now_select:
        if now_select!='Remove':
            add(now_select(x,y))
        else:
            for i in find(lambda a:a.contains((x,y))):
                remove(i)


#add simulton s to the simulation
def add(s):
    global object_pool
    object_pool.add(s)
    

# remove simulton s from the simulation    
def remove(s):
    global object_pool
    object_pool.remove(s)
    

#find/return a set of simultons that each satisfy predicate p    
def find(p):
    global object_pool
    return {i for i in object_pool if p(i)}

#call update for every simulton in the simulation
def update_all():
    global object_pool,cycle_count
    if running:
        cycle_count+=1
        dead_objects=set()
        for i in object_pool:
            temp=i.update()
            if temp:
                dead_objects|=temp
        for i in dead_objects:
            if type(i)!=tuple:
                remove(i)
            else:
                eval(i[1])(i[0])

#delete from the canvas every simulton in the simulation, and then call display for every
#  simulton in the simulation to add it back to the canvas possibly in a new location: to
#  animate it; also, update the progress label defined in the controller
def display_all():
    global object_pool
    for o in controller.the_canvas.find_all():
        controller.the_canvas.delete(o)
    
    for i in object_pool:
        i.display(controller.the_canvas)

    controller.the_progress.config(text="{} updates/{} simultons".format(cycle_count,len(object_pool)))
