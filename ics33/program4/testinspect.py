import inspect

class a:
    def __init__(self,f):
        self._f=f
    def get(self):
        return inspect.getsourcelines(self._f)[0]

b=a(lambda x:x**8)
print(b.get())
def func(a,b,c):
    a=b+1
    c=a+2
    b=c+3
    return a*b*c

c=a(func)
print(c.get())
