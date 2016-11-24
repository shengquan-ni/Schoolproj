
def check_core(types,args,sep):
    if not types:
        return []
    elif isinstance(types,dict):
        return Process_dict(types,args,sep)
    elif isinstance(types,tuple):
        return Process_tuple(types,args,sep)
    elif isinstance(types,list):
        return Process_list(types,args,sep)
    else:
        return Process_normal(types,args,sep)
        

def Process_normal(types,args,sep):
    try:
        result=types(args)
        return [result] if not isinstance(result,bool) else args if result else None
    except:
        if types==args:
            return [args]
        elif types==args.upper():
            return [args.upper()]
        return None


            

def Process_dict(types,args,sep):
    for i in types.keys():
        k=args.find(sep) if sep and args.find(sep)!= -1 else None
        tempres=check_core(i,args[:k],sep)
        if tempres:
            tempres2=check_core(types[i],args[k:].strip(),sep)
            if tempres2!=None:
                return tempres+tempres2
            else:
                return None

def Process_tuple(types,args,sep):
    res=None
    for i in types:
        try:
            if res!=None:
                if callable(i):
                    temp=i(res)
                else:
                    return check_core(i,temp,sep)
            else:
                k=args.find(sep) if sep and args.find(sep)!=-1 else None
                if callable(i):
                    temp=i(args[:k])
                else:
                    return check_core(i,args[:k],sep)
            if not isinstance(temp,bool):
                res=temp
            elif not temp:
                return None
            elif res==None:
                res=args[:k]
        except:
            return None
    return [res]

def Process_list(types,args,sep):
    result=[]
    for i in types:
        r=check_core(i,args,sep)
        if r!=None:
            result+=r
            args=args.split(sep,maxsplit=len(r))[-1]
        else:
            return None
    return result



def check_type(types,errormessage='ERROR',hint='',sep=' '):
    while True:
        args=input(hint)
        result=check_core(types,args,sep)
        if result!=None:
            if len(result)!=1:
                return result
            else:
                return result[0]
        print(errormessage)



print(check_type([lambda x:x[1]=='a',lambda y:y[1]=='b']))


