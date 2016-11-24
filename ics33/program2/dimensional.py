# Submitter: shenqgun(Shengquan, Ni)
# Partner  : changchs(Changchuan, Shen)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
from goody import type_as_str
from math import sqrt


class DimensionError(Exception):
    def __init__(self,message=None):
        Exception.__init__(self,message)


class Dimensional:
    def __init__(self,v,l=0,m=0,t=0):
        assert type(v)==int or type(v)==float
        assert all(type(i)==int for i in [l,m,t])
        self.v,self.l,self.m,self.t=v,l,m,t

    def __bool__(self):
        return self.v!=0

    def __len__(self):
        return abs(self.l)+abs(self.m)+abs(self.t)

    def __repr__(self):
        return 'Dimensional({}'.format(self.v)+(',l={}'.format(self.l)if self.l else '')+\
               (',m={}'.format(self.m) if self.m else '')+(',t={}'.format(self.t)if self.t else '')+')'

    def __str__(self):
        return '{}({},{},{})'.format(self.v,self.l,self.m,self.t)

    def __getitem__(self,k):
        m={'value':self.v,'l':self.l,'m':self.m,'t':self.t,'d':(self.l,self.m,self.t)}
        if k in m:return m[k]
        else:raise KeyError

    def format(self,arg):
        func=lambda x,y,f:'' if y==0 else (('' if y>0 else '/' if not f else '1/')+str(x)+('**{}'.format(abs(y)) if abs(y)!=1 else ''))
        return str(self.v) + (' ' if self['d']!=(0,0,0) else '')+''.join([func(arg[i],self['d'][i],any([k<0 for k in self['d']]) and all([k<=0 for k in self['d']])) for i in range(3)])

    def __pos__(self):
        return Dimensional(self.v,*self['d'])

    def __neg__(self):
        return Dimensional(-self.v,*self['d'])

    def op_base(self,arg,op):
        if type(self)!=type(arg) and type(arg)!=int and type(arg)!=float:
            raise TypeError
        elif type(arg)!=type(self):
            if self['d']==(0,0,0):
                return Dimensional(op(self.v,arg),*self['d'])
            else:
                raise DimensionError
        elif arg['d']!=self['d']:
            raise DimensionError
        else:
            return Dimensional(op(self.v,arg.v),*self['d'])

    def op_base2(self,arg,op,op2):
        if type(self)!=type(arg) and type(arg)!=int and type(arg)!=float:
            raise TypeError
        elif type(arg)!=type(self):
            return Dimensional(op(self.v,arg),*(op2(self['d'][i],0) for i in range(3)))
        else:
            return Dimensional(op(self.v,arg.v),*(op2(self['d'][i],arg['d'][i]) for i in range(3)))

    def __add__(self,arg):
        return self.op_base(arg,lambda x,y:x+y)
            
    def __radd__(self,arg):
        return self.__add__(arg)

    def __sub__(self,arg):
        return self.op_base(arg,lambda x,y:x-y)

    def __rsub__(self,arg):
        return self.op_base(arg,lambda x,y:y-x)

    def __mul__(self,arg):
        return self.op_base2(arg,lambda x,y:x*y,lambda x,y:x+y)

    def __rmul__(self,arg):
        return self.__mul__(arg)

    def __truediv__(self,arg):
        return self.op_base2(arg,lambda x,y:x/y,lambda x,y:x-y)

    def __rtruediv__(self,arg):
        return self.op_base2(arg,lambda x,y:y/x,lambda x,y:y-x)

    def __pow__(self,arg):
        if type(self)!=type(arg) and type(arg)!=int:
            raise TypeError
        elif type(arg)!=type(self):
                return Dimensional(self.v**arg,*(i*arg for i in self['d']))
        elif arg['d']!=(0,0,0):
            raise DimensionError
        else:
            return Dimensional(self.v**arg.v,*(i*arg.v for i in self['d']))

    def cmp_base(self,arg,cmp):
        if type(self)!=type(arg) and type(arg)!=int and type(arg)!=float:
            raise TypeError
        elif type(self)==type(arg):
            if arg['d']!=self['d']:
                raise DimensionError
            else:
                return cmp(self.v,arg.v)
        else:
            return cmp(self.v,arg)
        
    def __lt__(self,arg):
        return self.cmp_base(arg,lambda x,y:x<y)

    def __gt__(self,arg):
        return self.cmp_base(arg,lambda x,y:x>y)

    def __le__(self,arg):
        return self.cmp_base(arg,lambda x,y:x<=y)

    def __ge__(self,arg):
        return self.cmp_base(arg,lambda x,y:x>=y)

    def __eq__(self,arg):
        return self.cmp_base(arg,lambda x,y:x==y)

    def __ne__(self,arg):
        return self.cmp_base(arg,lambda x,y:x!=y)

    def __abs__(self):
        return Dimensional(abs(self.v),*self['d'])

    def sqrt(self):
        if any([i%2==1 for i in self['d']]):raise DimensionError
        return Dimensional(sqrt(self.v),*(int(i/2) for i in self['d']))

    def __setattr__(self,k,v):
        assert k in ('v','l','m','t') and not k in self.__dict__
        self.__dict__[k]=v

        


if __name__ == '__main__':
    # You can put your own code to test Dimensional here; for example
    t = Dimensional(2.5,t=1)
    g = Dimensional(9.8,l=1,t=-2)
    d = .5*g*t**2
    print(d.format("mgs"))
    
    
    #driver tests
    import driver
    driver.default_file_name = 'bsc2.txt'
#     driver.default_show_exception         = True
#     driver.default_show_exception_message = True
#     driver.default_show_traceback         = True
    #driver.driver()
