#include <algorithm>

#include "chessalgorithm.h"
#include "chessboard.h"
#include "chessview.h"
#include "pieces.h"
#include "utils.h"

#define DEPTH 7

ChessAlgorithm::ChessAlgorithm(QObject *parent) : QObject(parent)
{
    m_board=NULL;
    m_currentPlayer=NoPlayer;
    m_result=NoResult;
}

ChessBoard* ChessAlgorithm::board() const
{
    return m_board;
}

void ChessAlgorithm::setBoard(ChessBoard *board)
{
    if(board == m_board) {
        return;
    }
    delete m_board;
    m_board = board;
    emit boardChanged(m_board);
}

void ChessAlgorithm::setupBoard()
{
    setBoard(new ChessBoard(8, 8, this));
}

void ChessAlgorithm::newGame()
{
    setupBoard();
    QVector<QVector<char> > matrix(8,QVector<char>(8,' '));
    matrix[0]={'r','n','b','q','k','b','n','r'};    //black pieces
    matrix[1]={'p','p','p','p','p','p','p','p'};
    matrix[6]={'P','P','P','P','P','P','P','P'};    //white pieces
    matrix[7]={'R','N','B','Q','K','B','N','R',};
    board()->setFen(matrix);
}

void ChessAlgorithm::setResult(Result value)
{
    if(result() == value){
        return;
    }
    else if(result() == NoResult) {
        m_result = value;
        emit gameOver(m_result);
    } else {
        m_result = value;
    }
}

void ChessAlgorithm::setCurrentPlayer(Player value)
{
    if(currentPlayer() == value)
        return;

    m_currentPlayer = value;
    emit currentPlayerChanged(m_currentPlayer);
}

void display(const QVector<QVector<Piece*> >& board)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            cout<<(char)*board[i][j]<<" "; // check i,j if required

        cout<<"\n";
    }
    cout<<"\n";
}

QVector< QVector<QVector<Piece*> > > ChessAlgorithm::generateMoves(QVector<QVector<Piece*> >& board,int depth)
{
    //maximise for black piece - small letters - depth is even
    //minimise for white piece - capital letters - depth is odd
    QVector< QVector<QVector<Piece*> > > boardStates;

    boardStates.clear();
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if((depth%2==0 && islower(*board[i][j])) ||
               (depth%2==1 && isupper(*board[i][j])) )
            {
                board[i][j]->allMoves(board, boardStates,i,j);
            }
        }
    }
    return boardStates;
}

QVector<QVector<Piece*> > ChessAlgorithm::minimax(QVector<QVector<Piece*> > board, int depth, int& alpha, int& beta)
{
    //base case
    if(depth==DEPTH)
    {
        return board;
    }

    QVector<QVector<QVector<Piece*> > > boardStates=generateMoves(board,depth);
    random_shuffle(boardStates.begin(), boardStates.end());
    int minimizing=depth%2;

    //maximise for even levels and minimise for odd levels
    int val=!minimizing?INT_MIN:INT_MAX;
    QVector<QVector<Piece*> > nextBoardState,resultBoardState; int nextBoardStateScore;
    for(int i=0;i<boardStates.size();i++)
    {
        nextBoardState = minimax(boardStates[i],depth+1,alpha, beta);
        nextBoardStateScore = calculateScore(nextBoardState);
        if(!minimizing)
        {
            if(nextBoardStateScore>val)
            {
                val=nextBoardStateScore;
                resultBoardState=boardStates[i];
            }
            alpha = max(alpha, val);
            if(beta<=alpha)
                break;
        }
        else if(minimizing)
        {
            if(nextBoardStateScore<val)
            {
                val=nextBoardStateScore;
                resultBoardState=boardStates[i];
            }
            beta=min(beta,val);
            if(beta<=alpha)
                break;
        }
    }
    return resultBoardState;
}
void ChessAlgorithm::AIMove()
{
    cout<<"From: "<<"\n";   display(m_board->getBoard());
    int alpha = INT_MIN;
    int beta = INT_MAX;
    QVector<QVector<Piece*> > result=minimax(m_board->getBoard(),0, alpha, beta);
    cout<<"To: "<<"\n";     display(result);
    QVector<QVector<int> > m;
    for (int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(m_board->data(j+1,i+1)->getLabel() != result[i][j]->getLabel())
                m.push_back({i,j});

        }
    }

    if(*result[m[0][0]][m[0][1]]==' ')
    {
        //move board[m[0][0]][m[0][1]] to board[m[1][0]][m[1][1]]
        m_board->setData(m[1][1]+1,m[1][0]+1,*m_board->data(m[0][1]+1,m[0][0]+1));
        m_board->setData(m[0][1]+1, m[0][0]+1, ' ');
    }
    else if(*result[m[1][0]][m[1][1]]==' ')
    {
        //move board[m[1][0]][m[1][1]] to board[m[0][0]][m[0][1]]
        m_board->setData(m[0][1]+1,m[0][0]+1,*m_board->data(m[1][1]+1,m[1][0]+1));
        m_board->setData(m[1][1]+1,m[1][0]+1,' ');
    }
    else
        cout<<"Invalid move\n";
}
