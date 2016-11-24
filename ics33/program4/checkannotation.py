# Submitter: shenqgun(Shengquan, Ni)
# Partner  : changchs(Changchuan, Shen)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
from goody import type_as_str
import inspect

class Check_All_OK:
    """
    Check_All_OK class implements __check_annotation__ by checking whether each
      annotation passed to its constructor is OK; the first one that
      fails (by raising AssertionError) prints its problem, with a list of all
      annotations being tried at the end of the check_history.
    """
       
    def __init__(self,*args):
        self._annotations = args
        
    def __repr__(self):
        return 'Check_All_OK('+','.join([str(i) for i in self._annotations])+')'

    def __check_annotation__(self, check, param, value,check_history):
        for annot in self._annotations:
            check(param, annot, value, check_history+'Check_All_OK check: '+str(annot)+' while trying: '+str(self)+'\n')


class Check_Any_OK:
    """
    Check_Any_OK implements __check_annotation__ by checking whether at least
      one of the annotations passed to its constructor is OK; if all fail 
      (by raising AssertionError) this classes raises AssertionError and prints
      its failure, along with a list of all annotations tried followed by the
      check_history.
    """
    
    def __init__(self,*args):
        self._annotations = args
        
    def __repr__(self):
        return 'Check_Any_OK('+','.join([str(i) for i in self._annotations])+')'

    def __check_annotation__(self, check, param, value, check_history):
        failed = 0
        for annot in self._annotations: 
            try:
                check(param, annot, value, check_history)
            except AssertionError:
                failed += 1
        if failed == len(self._annotations):
            assert False, repr(param)+' failed annotation check(Check_Any_OK): value = '+repr(value)+\
                         '\n  tried '+str(self)+'\n'+check_history                 



class Check_Annotation():
    # set this name to True for checking to occur
    checking_on  = True
  
    # self._checking_on must also be true for checking to occur
    def __init__(self,f):
        self._f = f
        self.checking_on = True
    # Check whether param's annot is correct for value, adding to check_history
    #    if recurs; defines many local function which use it parameters.  
    def check(self,param,annot,value,check_history=''):

        # Define local functions for checking, list/tuple, dict, set/frozenset,
        #   lambda/functions, and str (str for extra credit)
        # Many of these local functions called by check, call check on their
        #   elements (thus are indirectly recursive)
        def make_message(p,a,v,c,error='wrong type',e=''):
            return (
                   '{p} failed annotation check({error}):value= {v}\nwas type {tv} ...should be type {a}\n'.format(p=p,error=error,v=v,tv=type_as_str(v),a=type_as_str(a) if type(a)!=type else a) if error=='wrong type' else\
                   '{p} annotation inconsistency: {a} should have 1 value but had {la}'.format(p=p,a=type_as_str(a),la=len(a)) if error=='annotation inconsistency' else\
                   '{p} failed annotation check({error}): value = {v}\nannotation had {la} elements{a}'.format(p=p,v=v,la=len(a),a=a,error=error) if error=='wrong number of elements' else\
                   '{p} annotation predicate({a}) raised exception\nexception={te}:{e}'.format(p=p,a=a,e=e,te=type(e)) if error=='lambda raised exception' else\
                   '{p} annotation inconsistency: predict should have 1 parameter but had {la}\n predict={a}'.format(p=p,a=a,la=len(a.__code__.co_varnames)) if error=='lambda error' else\
                   '{p} failed annotation check: value = {v}\npredict={a}'.format(p=p,v=v,a=a) if error=='lambda return False' else\
                   '{p} failed annotation check(str predicate: {a})\nargs for evaluation: {s}'.format(p=p,a=a,s=''.join(['{}->{} '.format(k,v) for k,v in self.temp.items()])) if error=='eval failed' else\
                   '{p} annotation check(str predicate: {a}) raised exception\nexception={te}:{e}'.format(p=p,a=a,e=e,te=type(e)) if error=='eval exception' else\
                   '{p} annotation undecipherable: {a}'.format(p=p,a=repr(a)))\
                   +c
        # Decode the annotation here and then check it
        if annot==None:
            return
        if inspect.isfunction(annot):
            assert len(annot.__code__.co_varnames)==1,make_message(param,annot,value,check_history,'lambda error')
            result=False
            try:
                result=annot(value)
            except Exception as e:
                raise AssertionError(make_message(param,annot,value,check_history,'lambda raised exception',e))
            assert result,make_message(param,annot,value,check_history,'lambda return False')
        else:
            if any(isinstance(annot,i) for i in [dict,list,tuple,set,frozenset]) or any(annot==i for i in [int,float,str,list,dict,tuple,set,frozenset]):
                assert type(value)==annot if type(annot)==type(type) else type(value)==type(annot),make_message(param,annot,value,check_history)
                if any(annot==i for i in [int,float,str,list,dict,tuple,set,frozenset]):return
            if isinstance(annot,dict):
                if len(annot)==0:return
                assert len(annot)==1,make_message(param,annot,value,check_history,'annotation inconsistency')
                k,v=list(annot)[0],annot[list(annot)[0]]
                for vk,vv in value.items():
                    self.check(param,k,vk,check_history+'dict key check: {}\n'.format(k))
                    self.check(param,v,vv,check_history+'dict value check: {}\n'.format(v))
            elif isinstance(annot,list) or isinstance(annot,tuple):
                if len(annot)==0:return 
                elif len(annot)==1:
                    for n,i in enumerate(value):
                        self.check(param,annot[0],i,check_history+'{}[{}] check: {}\n'.format(type_as_str(annot),n,annot[0]))
                elif len(annot)>1:
                    assert len(annot)==len(value),make_message(param,annot,value,check_history,'wrong number of elements')
                    for i in range(len(annot)):
                        self.check(param,annot[i],value[i],check_history+'{}[{}] check: {}\n'.format(type_as_str(annot),i,annot[i]))
            elif isinstance(annot,set) or isinstance(annot,frozenset):
                if len(annot)==0:return
                assert len(annot)==1,make_message(param,annot,value,check_history,'annotation inconsistency')
                for i in value:
                    self.check(param,list(annot)[0],i,check_history+'{} value check: {}\n'.format(type_as_str(annot),list(annot)[0]))
            elif isinstance(annot,str):
                try:
                    assert eval(annot,self.temp),make_message(param,annot,value,check_history,'eval failed')
                except Exception as e:
                    assert False,make_message(param,annot,value,check_history,'eval exception',e)
            elif hasattr(annot,'__check_annotation__'):
                annot.__check_annotation__(self.check,param,value,check_history)
            else:
                assert False,make_message(param,annot,value,check_history,'undecipherable')
            
        
    # Return result of calling decorated function call, checking present
    #   parameter/return annotations if required
    def __call__(self, *args, **kargs):
        
        # Return a dictionary of the parameter/argument bindings (actually an
        #    ordereddict, in the order parameters occur in the function's header)
        def param_arg_bindings():
            f_signature  = inspect.signature(self._f)
            bound_f_signature = f_signature.bind(*args,**kargs)
            for param in f_signature.parameters.values():
                if param.name not in bound_f_signature.arguments:
                    bound_f_signature.arguments[param.name] = param.default
            return bound_f_signature.arguments
        
        # If annotation checking is turned off at the class or function level
        #   just return the result of calling the decorated function
        # Otherwise do all the annotation checking
        if Check_Annotation.checking_on==False or self.checking_on==False:
            return self._f(*args,**kargs)
        self.temp,annots=param_arg_bindings(),self._f.__annotations__
        self.temp['_return']=None
        try:
            # Check the annotation for every parameter (if there is one)
            for k,v in self.temp.items():      
            # Compute/remember the value of the decorated function
                self.check(k,annots[k] if k in annots else None,v)
            result=self._f(*args,**kargs)
            # If 'return' is in the annotation, check it
            if 'return' in annots:
                self.temp['_return']=result
                self.check('_return',annots['return'],self.temp['_return'])
            # Return the decorated answer
            return result
            
        # On first AssertionError, print the source lines of the function and reraise 
        except AssertionError:
            #print(80*'-')
            #for l in inspect.getsourcelines(self._f)[0]: # ignore starting line #
            #    print(l.rstrip())
            #print(80*'-')
            raise 




  
if __name__ == '__main__':     
    # an example of testing a simple annotation

           
    import driver
    driver.driver()
