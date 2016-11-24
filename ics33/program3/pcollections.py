# Submitter: shenqgun(Shengquan, Ni)
# Partner  : yangguah(Yangguang, He)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
import re, traceback, keyword

def pnamedtuple(type_name, field_names, mutable=False):
    def show_listing(s):
        for i, l in enumerate(s.split('\n'), 1):
            print(' {num: >3} {txt}'.format(num=i, txt=l.rstrip()))

    # put your code here
    # bind class_definition (used below) to the string constructed for the class
    if type(field_names)==str:
        fields=[i for i in field_names.replace(',',' ').split()]
    elif type(field_names)==list:
        fields=field_names
    else:
        raise SyntaxError
    if type(type_name)!=str or not all(re.search('^[A-Za-z]\w*$',i)!=None for i in [type_name]+fields) or any(i in keyword.kwlist for i in [type_name]+fields):
        raise SyntaxError
    class_definition='''\
class {type_name}:
    def __init__(self,{args}):
        def normsetattr(self,k,v):
            self.__dict__[k]=v
        {type_name}.__setattr__=normsetattr
        self._fields={fields}
        self._mutable={mutable}
        for i,j in zip({fields},[{args}]):
            self.__dict__[i]=j
        if not self._mutable:
            def setattr(self,k,v):
                raise AttributeError
            {type_name}.__setattr__=setattr
{gets}
    def __repr__(self):
        return '{type_name}('+''.join(i+'='+repr(self.__dict__[i])+',' for i in self._fields)[:-1]+')'
    def __eq__(self,arg):
        return type(self)==type(arg) and all(self[i]==arg[i] for i in range(len(self._fields)))
    def __getitem__(self,data):
        if type(data)==int and data<len(self._fields):
            return self.__dict__[self._fields[data]]
        elif type(data)==str and data in self.__dict__:
            return self.__dict__[data]
        else:
            raise IndexError
    def _replace(self,**kwargs):
        if any(i not in self.__dict__ for i in kwargs):
            raise TypeError
        if self._mutable:
            for i in kwargs:
                self.__dict__[i]=kwargs[i]
        else:
            return {type_name}(*[self[i] if i not in kwargs else kwargs[i] for i in self._fields])
                
    '''.format(type_name=type_name,args=''.join(i+',' for i in fields)[:-1],fields=fields,mutable=mutable,gets=''.join('    def get_{}(self):return self.{}\n'.format(i,i) for i in fields)[:-1])
    # For initial debugging, always show the source code of the class
    #show_listing(class_definition)
    
    # Execute the class_definition string in a local namespace and then bind the
    #   name source_code in its dictionary to the class_defintion; return the
    #   class object created; if there is a syntax error, list the class and
    #   also show the error
    name_space = dict(__name__='pnamedtuple_{type_name}'.format(type_name=type_name))
    try:
        exec(class_definition,name_space)
        name_space[type_name].source_code = class_definition
    except(SyntaxError, TypeError):
        show_listing(class_definition)
        traceback.print_exc()
    return name_space[type_name]


    
if __name__ == '__main__':
    import driver
    driver.driver()
