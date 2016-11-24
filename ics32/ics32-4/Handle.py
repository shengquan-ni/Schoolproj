#Shengquan Ni 46564157 lab assignment 4
from Othello_Game import *

def cmd_display(GAME):
    '''display the othello game on console(idle)'''
    stats=GAME.get_stats()
    print('B: {}  W: {}'.format(stats['B'],stats['W']))
    for i in range(len(GAME.board)):
        for j in range(len(GAME.board[i])):
            print(GAME.board[i][j],end=' ')
        print()
    if GAME.isover:
        print('WINNER: {}'.format(GAME.get_winner()))
    else:
        print('TURN: {}'.format(GAME.turn))


def cmd_generate_input():
    '''receive user-inputs and return them'''
    NUM_OF_ROWS=check_type((int,lambda x:x>=4 and x<=16 and not x%2))
    NUM_OF_COLS=check_type((int,lambda x:x>=4 and x<=16 and not x%2))
    FIRST_MOVE=check_type({'W':None,'B':None})
    TOP_LEFT=check_type({'W':None,'B':None})
    WIN_DETERMINE=check_type({'>':None,'<':None})
    return (NUM_OF_ROWS,NUM_OF_COLS,FIRST_MOVE,TOP_LEFT,WIN_DETERMINE)


def cmd_drop_input(GAME):
    '''receive user-input then check if it is vaild position for the current player, if so, drop it to the game board'''
    if GAME.isover:
        print('GAME IS OVER')
        return None
    func=lambda x: lambda y: int(y)>=1 and int(y)<=len(x) 
    pos=[int(i)-1 for i in check_type([func(GAME.board),func(GAME.board[0])],errormessage='INVALID')]
    while not tuple(pos) in GAME.vaildpos:
        print('INVAILD')
        pos=[int(i)-1 for i in check_type([func(GAME.board),func(GAME.board[0])],errormessage='INVALID')]
    print('VALID')
    return pos


if __name__=='__main__':
    print('FULL')
    Game=Othello_Game(cmd_generate_input())
    Game.mainlogic(cmd_drop_input,cmd_display)
