#Shengquan Ni 46564157 and Changchuan Shen 83371717
from connectfour import *

switch={RED:'R',YELLOW:'Y',NONE:'.'}

def display(game_state: GameState):
    '''display the game board'''
    for i in range(1,BOARD_COLUMNS+1):
        print(i,end=' ')
    print()
    for i in range(BOARD_ROWS):
        for j in range(BOARD_COLUMNS):
            print(switch[game_state.board[j][i]],end=' ')
        print()

def process(game,droporpop,colnum):
    '''drop or pop one column'''
    if droporpop=='DROP':
        return drop(game,colnum-1)
    else:
        return pop(game,colnum-1)


def mainlogic(inputfunc,*args):
    '''the main logic of the connectfour'''
    game=new_game()
    whowins=NONE
    while whowins==NONE:
        droporpop,colnum=inputfunc(*args)
        if droporpop!=None and colnum!=None:
            print(droporpop,colnum)
            game=process(game,droporpop,colnum)
            whowins=winner(game)
            display(game)
    print('Red Wins!') if whowins==RED else print('Yellow Wins!')

def inputfunc():
    '''user input of a console-game'''
    droporpop=check_type((lambda x:x.strip(),{'DROP':None,'POP':None,(lambda x:'DROP' if x.upper()=='D' else False):None,(lambda x:'POP' if x.upper()=='P' else False):None}),sep=None,hint='DROP OR POP?\n',errormessage="Please enter 'DROP' or 'POP'or 'D' or 'P'")
    whichcol=check_type((int,lambda x:x>=1 and x<=BOARD_COLUMNS),hint='typing a number between 1 and 7 to specify a column\n',errormessage='Wrong column number',sep=None)
    return droporpop,whichcol        



'function of standardize one-line-user-input'
'''
author: Shengquan Ni
date:1/27/2016
'''
def check_core(types,args,sep):
    if not types:
        return []
    elif isinstance(types,dict):
        Process_dict(types,args,sep)
    elif isinstance(types,tuple):
        Process_tuple(types,args,sep)
    elif isinstance(types,list):
        Process_list(types,args,sep)
    else:
        Process_normal(types,args,sep)
        

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

