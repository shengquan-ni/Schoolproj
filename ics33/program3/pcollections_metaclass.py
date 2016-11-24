import re, traceback, keyword

def pnamedtuple(type_name,field_names,mutable=False):
    if type(field_names)==str:
        fields=[i for i in field_names.replace(',',' ').split()]
    elif type(field_names)==list:
        fields=field_names
    else:
        raise SyntaxError
    if type(type_name)!=str or not all(re.search('^[A-Za-z]\w*$',i)!=None for i in [type_name]+fields) or any(i in keyword.kwlist for i in [type_name]+fields):
        raise SyntaxError
    class MyMeta(type):
        def __init__(cls,tn,orc,fn):
            
            def initfunc(self,*args,**kwargs):
                
                def normsetattr(self,k,v):
                    self.__dict__[k]=v
                cls.__setattr__=normsetattr
                
                self._fields=[i for i in fields]
                self._mutable=mutable
                if len(args)+len(kwargs)!=len(fields):
                    raise TypeError
                for i in range(len(args)):
                    self.__setattr__(self._fields[i],args[i])
                for i in kwargs:
                    if not i in self.__dict__:
                        self.__setattr__(i,kwargs[i])
                    else:
                        raise TypeError
                if not self._mutable:
                    def setattr(self,k,v):
                        raise AttributeError
                    cls.__setattr__=setattr
            cls.__init__=initfunc
            
            for i in fields:
                exec('cls.get_{}=lambda self:self.{}'.format(i,i))
                
            def _replace(self,**kwargs):
                if any(i not in self.__dict__ for i in kwargs):
                    raise TypeError
                if self._mutable:
                    for i in kwargs:
                        self.__dict__[i]=kwargs[i]
                else:
                    return cls(*[self[i] if i not in kwargs else kwargs[i] for i in self._fields])
            cls._replace=_replace
            cls.source_code='Can not get the source code'
    class MyOverride:
        def __repr__(self):
            return '{}('.format(type_name)+''.join(i+'='+repr(self.__dict__[i])+',' for i in self._fields)[:-1]+')'
        def __getitem__(self,data):
            if type(data)==int and data<len(self._fields):
                return self.__dict__[self._fields[data]]
            elif type(data)==str and data in self.__dict__:
                return self.__dict__[data]
            else:
                raise IndexError
        def __eq__(self,arg):
            return type(self)==type(arg) and all(self[i]==arg[i] for i in range(len(self._fields)))

    return MyMeta(type_name,(MyOverride,),{i:None for i in fields})

if __name__ == '__main__':
    import driver
    driver.driver()
