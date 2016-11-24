#Shengquan Ni 46564157 and Changchuan Shen 83371717
from mynetwork import *

flag=True

def inputfunc_net(*args):
    '''
    the input of user goes first
    then receive server's response
    return a string indicate 'DROP' or 'POP' with a number of vaild column
    '''
    global flag
    s,droporpop,whichcol=args
    if flag:
        droporpop,whichcol=inputfunc()
        if send_and_recv(s,droporpop+' '+str(whichcol)).find('INVALID')!=-1:
            recv(s)
            print('INVAILD INPUT!')
            return None,None
        else:
            flag=False
            return droporpop,whichcol
    else:
        flag=True
        return translate(recv(s))


if __name__=='__main__':
    droporpop,whichcol='',''
    s=build_connection()
    if s:
        mainlogic(inputfunc_net,s,droporpop,whichcol)
