#Shengquan Ni 46564157 and Changchuan Shen 83371717
import socket
from general import *

def build_connection():
    '''
    build a connection of a specfic host with a specfic port
    then initialize ICS32 connectfour with the server
    '''
    s=socket.socket()
    host=input('host:')
    port=check_type((int,lambda x:x>=0 and x<=65535),hint='port:',errormessage='PORT must be integer and between 0 and 65535',sep=None)
    try:
        s.connect((host,port))
        playername=check_type((lambda x:x!='' and len(x.split())==1 and len(x.strip())==len(x)),hint='playername:',errormessage='Please re-enter your playername',sep=None)
        send_and_recv(s,'I32CFSP_HELLO '+playername)
        send_and_recv(s,'AI_GAME')
        return s
    except Exception as e:
        print(e)
        print('CONNECTION ERROR')
        s.close()
        return None

def send(s,message):
    '''send message to server'''
    s.send((message+'\r\n').encode())

def recv(s,recvcount=1):
    '''receive responses from server for 'recvcount' times'''
    result=''
    for i in range(recvcount):
        temp=s.recv(4096).decode()
        result+=temp
    return result
    

def send_and_recv(s,message,recvcount=1):
    '''send and recieve responses'''
    send(s,message)
    return recv(s,recvcount)

def translate(message):
    '''translate message to the format of 'DROP X' or 'POP X'
    '''
    message=message.split('\n')
    if message[0].find('DROP') or message[0].find('POP'):
        a,b=message[0].split()
        return a,int(b)
    else:
        return None,None
    
