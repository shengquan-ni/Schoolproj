#Shengquan Ni 46564157 lab assignment 4
Opposite={'W':'B','B':'W'}

class Othello_Game:
    def __init__(self,data):
        '''initialize the othello game board based on the five-line-user-input'''
        NUM_OF_ROWS,NUM_OF_COLS,FIRST_MOVE,TOP_LEFT,WIN_DETERMINE=data
        CHESS=[['.' for i in range(NUM_OF_ROWS)]for j in range(NUM_OF_COLS)]
        BOTTOM_RIGHT_Y=int(NUM_OF_COLS/2)
        BOTTOM_RIGHT_X=int(NUM_OF_ROWS/2)
        if TOP_LEFT=='W':
            CHESS[BOTTOM_RIGHT_Y-1][BOTTOM_RIGHT_X-1]='W'
            CHESS[BOTTOM_RIGHT_Y][BOTTOM_RIGHT_X]='W'
            CHESS[BOTTOM_RIGHT_Y][BOTTOM_RIGHT_X-1]='B'
            CHESS[BOTTOM_RIGHT_Y-1][BOTTOM_RIGHT_X]='B'
        else:
            CHESS[BOTTOM_RIGHT_Y-1][BOTTOM_RIGHT_X-1]='B'
            CHESS[BOTTOM_RIGHT_Y][BOTTOM_RIGHT_X]='B'
            CHESS[BOTTOM_RIGHT_Y][BOTTOM_RIGHT_X-1]='W'
            CHESS[BOTTOM_RIGHT_Y-1][BOTTOM_RIGHT_X]='W'
        self.board=CHESS
        self.turn=FIRST_MOVE
        self.vaildpos=[]
        self.isover=False
        self.stats={'W':2,'B':2,'.':NUM_OF_COLS*NUM_OF_ROWS-4}
        self.win_determine=WIN_DETERMINE
        self.__vaild_check()

    def __vaild_check(self):
        '''refresh the valid drop positions for current player(white or black)'''
        list=[]
        for i in range(len(self.board)):
            for j in range(len(self.board[i])):
                if self.board[i][j]=='.' and self.__vaild_drop((i,j)):
                    list.append((i,j))
        self.vaildpos=list

    def __vaild_drop(self,pos):
        '''check if the position is vaild for current player'''
        width=len(self.board[0])
        height=len(self.board)
        for i in range(-1,2):
            for j in range(-1,2):
                if i!=0 or j!=0:
                    x=pos[1]+j
                    y=pos[0]+i
                    flag=False
                    while x>=0 and x<width and y<height and y>=0:
                        TEMP=self.board[y][x]
                        if TEMP=='.':
                            break
                        elif TEMP==Opposite[self.turn]:
                            flag=True
                        else:
                            if flag:
                                return True
                            else:
                                break
                        x+=j
                        y+=i
        return False


    def __turn_the_dices(self,pos,i,j,width,height):
        '''turn the dices from one drop position to a single direction'''
        x=pos[1]+j
        y=pos[0]+i
        while x>=0 and x<width and y<height and y>=0:
            TEMP=self.board[y][x]
            if TEMP=='.':
                break
            elif TEMP==self.turn:
                while x!=pos[1] or y!=pos[0]:
                    if self.board[y][x]!=self.turn:
                        self.board[y][x]=self.turn
                        self.stats[self.turn]+=1
                        self.stats[Opposite[self.turn]]-=1
                    x-=j
                    y-=i
                break
            x+=j
            y+=i

    def drop(self,pos):
        '''drop one dice on the game board and turn the dices(8 directions)'''
        width=len(self.board[0])
        height=len(self.board)
        self.board[pos[0]][pos[1]]=self.turn
        self.stats[self.turn]+=1
        self.stats['.']-=1
        for i in range(-1,2):
            for j in range(-1,2):
                if i!=0 or j!=0:
                    self.__turn_the_dices(pos,i,j,width,height)
        self.turn=Opposite[self.turn]
        #check if current player has vaild drop positions
        self.__vaild_check()
        #if not
        if self.vaildpos==[]:
            #change turn to Opposite
            self.turn=Opposite[self.turn]
            #check if current player has vaild drop positions
            self.__vaild_check()
            #if not 
            if self.vaildpos==[]:
                #game over
                self.isover=True



    def get_stats(self):
        '''get current stats of the game'''
        return self.stats

    def get_winner(self):
        '''get winner of the game'''
        d=self.get_stats()
        if self.win_determine=='>':
            return 'W' if d['W']>d['B'] else 'B' if d['B']>d['W'] else 'NONE'
        else:
            return 'W' if d['W']<d['B'] else 'B' if d['B']<d['W'] else 'NONE'

    def mainlogic(self,inputfunc,displayfunc):
        '''the main logic of the othello game'''
        while not self.isover:
            displayfunc(self)
            pos=inputfunc(self)
            self.drop(pos)
        displayfunc(self)




'''

I use them as outside functions, so it is not a part of this project.
Thus I don't want to write any docstring to the function.

author: Shengquan Ni 
date: 2/27/2016
purpose: check if user input accords of specific format
'''    
def check_core(types,args,sep,level):
    if not types:
        return []
    elif isinstance(types,dict):
        return Process_dict(types,args,sep,level)
    elif isinstance(types,tuple):
        return Process_tuple(types,args,sep,level)
    elif isinstance(types,list):
        return Process_list(types,args,sep,level)
    else:
        return Process(types,args,sep,level)
            

def Process_dict(types,args,sep,level):
    for i in types.keys():
        k=args.find(sep) if sep and args.find(sep)!= -1 else None
        tempres=check_core(i,args[:k],sep,level+1)
        if tempres:
            tempres2=check_core(types[i],args[k+1 if k else None:],sep,level+1)
            if tempres2!=None:
                return tempres+tempres2
            else:
                return None

def Process_list(types,args,sep,level):
    result=[]
    for i in types:
        k=args.find(sep) if sep and args.find(sep)!=-1 else None
        r=check_core(i,args[:k],sep,level+1)
        if r!=None:
            result+=r
            if k:
                args=args[k+1:]
            else:
                args=''
        else:
            return None
    if not level and args!='':
        return None
    return result


def Process_tuple(types,args,sep,level):
    res=None
    for i in types:
        try:
            if res!=None:
                if callable(i):
                    temp=i(res)
                else:
                    return check_core(i,temp,sep,level+1)
            else:
                k=args.find(sep) if sep and args.find(sep)!=-1 else None
                if callable(i):
                    temp=i(args[:k])
                else:
                    return check_core(i,args[:k],sep,level+1)
            if not isinstance(temp,bool):
                res=temp
            elif not temp:
                return None
            elif res==None:
                res=args[:k]
        except:
            return None
    return [res]


def Process(types,args,sep,level):
    try:
        result=types(args)
        return [result] if not isinstance(result,bool) else [args] if result else None
    except:
        if types==args:
            return [args]
        elif types==args.upper():
            return [args.upper()]
        return None

def check_type(types,errormessage='ERROR',hint='',sep=' '):
    while True:
        args=input(hint)
        result=check_core(types,args,sep,0)
        if result!=None:
            if len(result)!=1:
                return result
            else:
                return result[0] 
        print(errormessage)







