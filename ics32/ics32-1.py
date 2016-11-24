#Shengquan Ni 46564157 and Yucheng Rong 75819508
import os,os.path,shutil,time,stat
from pathlib import Path

def check_core(types,args):
    if not types:
        return []
    elif isinstance(types,dict):
        for i in types.keys():
            k=args.find(' ') if args.find(' ')!= -1 else None
            tempres=check_core(i,args[:k])
            if tempres:
                tempres2=check_core(types[i],args[k:].strip())
                if tempres2!=None:
                    return tempres+tempres2
                else:
                    return None
    elif isinstance(types,tuple):
        res=None
        for i in types:
            try:
                if res!=None:
                    temp=i(res)
                else:
                    k=args.find(' ')
                    if k!=-1:
                        temp=i(args[:k])
                    else:
                        temp=i(args)
                if not isinstance(temp,bool):
                    res=temp
                elif not temp:
                    return None
            except Exception as e:
                print(e)
                return None
        return [res]
    elif isinstance(types,list):
        result=[]
        for i in types:
            r=check_core(i,args)
            if r!=None:
                result+=r
                args=args.split(maxsplit=len(r))[-1]
            else:
                return None
        return result
    else:
        try:
            return [types(args)]
        except:
            if types==args:
                return [args]
            elif types==args.upper():
                return [args.upper()]
            return None
            



def check_type(types,errormessage='ERROR'):
    while True:
        args=input()
        result=check_core(types,args)
        if result!=None:
            return result
        print(errormessage)
    



def recursive_walk(path):
    dirs,files=[],[]
    temp=os.listdir(path)
    for i in temp:
        if os.path.isdir(os.path.join(path,i)):
            dirs.append(i)
        else:
            files.append(i)
    yield path,dirs,files
    for i in dirs:
        for a,b,c in recursive_walk(os.path.join(path,i)):
            yield a,b,c


def handle():
    path=check_type((str,os.path.exists))[0]
    path=path+os.sep if not path.endswith(os.sep) else path
    mode1=check_type({'S':int,'N':str,'E':str})
    mode2=check_type({"P":None,"F":None,"D":None,"T":None})
    switch={
        'N':lambda x:os.path.basename(x)==mode1[1],
        'S':lambda x:os.path.getsize(x)>mode1[1],
        'E':lambda x:-1<os.path.splitext(os.path.basename(x))[1].find(mode1[1])<=1
        }
    for root, dirs, files in recursive_walk(path):
        result=filter(switch[mode1[0]],map(lambda x:os.path.join(root,x),files))
        for i in result:
            print(i)
            if mode2[0]=='F':
                temp=open(i,errors='ignore')
                try:
                    print(temp.readline().strip())
                except Exception as e:
                    print(e)
                temp.close()
            elif mode2[0]=='T':
                os.utime(i)
            elif mode2[0]=='D':
                shutil.copy(i,i+'.dup')



if __name__ == '__main__':
    handle()
