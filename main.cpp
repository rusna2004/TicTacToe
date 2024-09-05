#include <iostream>
using namespace std;

#define HUMAN 1
#define COMPUTER 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showboard(char board[][SIDE])
{
    cout<<"\t \t \t"<<board[0][0]<<"|"<<board[0][1]<<"|"<<board[0][2]<<"\n";
    cout<<"\t \t \t"<<"------------"<<"\n";
    cout<<"\t \t \t"<<board[1][0]<<"|"<<board[1][1]<<"|"<<board[1][2]<<"\n";
    cout<<"\t \t \t"<<"------------"<<"\n";
    cout<<"\t \t \t"<<board[2][0]<<"|"<<board[2][1]<<"|"<<board[2][2]<<"\n";
}

void showinstructions()
{
    cout<<"Choose cell numbered from 1 to 9 as shown below and play"<<"\n";
    cout<<"\t \t \t"<<1<<"|"<<2<<"|"<<3<<"|"<<"\n";
    cout<<"\t \t \t"<<"-----------"<<"\n";
    cout<<"\t \t \t"<<4<<"|"<<5<<"|"<<6<<"|"<<"\n";
    cout<<"\t \t \t"<<"-----------"<<"\n";
    cout<<"\t \t \t"<<7<<"|"<<8<<"|"<<9<<"|"<<"\n";
}

void initialise(char board[][SIDE])
{
    for(int i=0; i<SIDE; i++)
    {
        for(int j=0; j<SIDE; j++)
        {
            board[i][j]='*';
        }
    }
}

void declareWinner(int whoseturn)
{
    if(whoseturn == COMPUTER)
        cout<<"Computer won"<<endl;
    else
        cout<<"You won"<<endl;
}

bool rowCrossed(char board[][SIDE])
{
    for(int i=0; i<SIDE; i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='*')
            return true;
    }
    return false;
}

bool columnCrossed(char board[][SIDE])
{
    for(int i=0; i<SIDE; i++)
    {
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='*')
            return true;
    }
    return false;
}

bool diagonalCrossed(char board[][SIDE])
{
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='*')
        return true;
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='*')
        return true;
    return false;
}

bool gameOver(char board[][SIDE])
{
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score=0, bestscore=0;
    if(gameOver(board)==true)
    {
        if(isAI == true)
            return -10;
        else
            return 10;
    }
    else
    {
        if(depth<9)
        {
            if(isAI==true)
            {
                bestscore=-999;
                for(int i=0; i<SIDE; i++)
                {
                    for(int j=0; j<SIDE; j++)
                    {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=COMPUTERMOVE;
                            score = minimax(board, depth+1, false);
                            board[i][j]='*';
                            if(score>bestscore)
                            {
                               bestscore = score;
                            }
                        }
                    }
                }
                return bestscore;
            }
            else
            {
                bestscore=999;
                for(int i=0; i<SIDE; i++)
                {
                    for(int j=0; j<SIDE; j++)
                    {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=HUMANMOVE;
                            score = minimax(board,depth+1,true);
                            board[i][j]='*';
                            if(score<bestscore)
                            {
                                bestscore = score;
                            }
                        }
                    }
                }
                return bestscore;
            }
        }
        else
        {
            return 0;
        }
    }
}

int bestMove(char board[][SIDE], int moveindex)
{
    int x=-1, y=-1;
    int score=0, bestscore=-999;
    for(int i=0; i<SIDE; i++)
    {
        for(int j=0; j<SIDE; j++)
        {
            if(board[i][j]=='*')
            {
                board[i][j]=COMPUTERMOVE;
                score = minimax(board, moveindex+1,false);
                board[i][j]='*';
                if(score>bestscore)
                {
                    bestscore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return (x*3 + y);
}

void playTicTacToe(int whoseturn)
{
    char board[SIDE][SIDE];
    int moveindex=0, x=0, y=0;
    initialise(board);
    showinstructions();
    while(gameOver(board)==false && moveindex!=SIDE*SIDE)
    {
        int n;
        if(whoseturn==COMPUTER)
        {
            n = bestMove(board,moveindex);
            x = n/SIDE;
            y = n%SIDE;
            board[x][y]=COMPUTERMOVE;
            cout<<"Computer has put 'O' in the cell "<<n+1<<endl;
            showboard(board);
            moveindex++;
            whoseturn = HUMAN;
        }
        else if(whoseturn==HUMAN)
        {
            cout<<"You can insert in the following positions"<<endl;
            for(int i=0; i<SIDE; i++)
            {
                for(int j=0; j<SIDE; j++)
                {
                    if(board[i][j]=='*')
                    {
                        cout<<3*i+j+1<<" ";
                    }
                }
            }
            cout<<endl;
            cout<<"Enter a position: ";
            cin>>n;
            n--;
            x = n/SIDE;
            y = n%SIDE;
            if(board[x][y]=='*' && n<9 && n>=0)
            {
                board[x][y]=HUMANMOVE;
                cout<<"You have put 'X' in the cell "<<n+1<<endl;
                showboard(board);
                moveindex++;
                whoseturn=COMPUTER;
            }
            else if(board[x][y]!='*' && n<9 && n>=0)
            {
                cout<<"Entered position is already occupied! Choose another position."<<endl;
            }
            else if(n<0 || n>8)
            {
                cout<<"Invalid position"<<endl;
            }
        }
    }

    if(gameOver(board)==false && moveindex==SIDE*SIDE)
    {
        cout<<"It's a draw"<<endl;
    }
    else
    {
        if(whoseturn == COMPUTER)
            whoseturn = HUMAN;
        else if(whoseturn == HUMAN)
            whoseturn = COMPUTER;
        declareWinner(whoseturn);
    }
}

int main()
{
    char ans = 'y';
    do
    {
        char choice;
        cout<<"Do you want to start first? (y/n) ";
        cin>>choice;
        if(choice == 'n')
            playTicTacToe(COMPUTER);
        else if(choice == 'y')
            playTicTacToe(HUMAN);
        else
            cout<<"Invalid choice"<<endl;

        cout<<"Do you want to quit? (y/n) ";
        cin>>ans;
    } while(ans == 'n');
    return 0;
}
