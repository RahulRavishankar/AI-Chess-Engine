#include <iostream>
#include <QDebug>
using namespace std;

#define DEPTH 3
#include "chessboard.h"

ChessBoard::ChessBoard(int ranks,int columns, QObject *parent) : QObject(parent),m_ranks(ranks),m_columns(columns)
{
    initBoard();
}
int ChessBoard::ranks()
{
    return m_ranks;
}

int ChessBoard::columns()
{
    return m_columns;
}

void ChessBoard::setRanks(int newRanks)
{
    if(ranks() == newRanks) {
    return;
    }
    m_ranks = newRanks;
    initBoard();
    emit ranksChanged(m_ranks);
}

void ChessBoard::setColumns(int newColumns)
{
    if(columns() == newColumns) {
    return;
    }
    m_columns = newColumns;
    initBoard();
    emit columnsChanged(m_columns);
}

void ChessBoard::initBoard()
{
    m_boardData.fill(QVector<char>(' ',8 ),8);
    emit boardReset();
}

char ChessBoard::data(int column, int rank) const
{
    return (m_boardData[rank-1])[column-1];
}

bool ChessBoard::setDataInternal(int column, int rank, char value)
{
    if(m_boardData[rank-1][column-1] == value) {
        return false;
    }
    m_boardData[rank-1][column-1]=value;
    return true;
}

void ChessBoard::setData(int column, int rank, char value)
{
    if(setDataInternal(column, rank, value)) {
    emit dataChanged(column, rank);
    }
}
bool ChessBoard::movePieceUtil(int fromColumn, int fromRank, int toColumn, int toRank)
{
    switch (m_boardData[fromRank][fromColumn]) {
        case 'p': case 'P': return piece.pawn.isValid(m_boardData,fromRank,fromColumn,toRank,toColumn); break;
        case 'n': case 'N': return piece.knight.isValid(m_boardData,fromRank,fromColumn,toRank,toColumn); break;
        case 'r': case 'R': return piece.rook.isValid(m_boardData,fromRank,fromColumn,toRank,toColumn); break;
        case 'b': case 'B': return piece.bishop.isValid(m_boardData,fromRank,fromColumn,toRank,toColumn); break;
        case 'q': case 'Q': return piece.queen.isValid(m_boardData,fromRank,fromColumn,toRank,toColumn); break;
        case 'k': case 'K': return piece.king.isValid(m_boardData,fromRank,fromColumn,toRank,toColumn); break;
        default:
            return false;
    }

}
void ChessBoard::movePiece(int fromColumn, int fromRank, int toColumn, int toRank)
{
    if(movePieceUtil(fromColumn-1,fromRank-1,toColumn-1,toRank-1))
    {
        setData(toColumn, toRank, data(fromColumn, fromRank));
        setData(fromColumn, fromRank, ' ');

        AIMove();
    }
}
void ChessBoard::setFen(const QVector<QVector<char> > &matrix)
{
    for(int i=0;i<ranks();i++)
        for(int j=0;j<columns();j++)
            setDataInternal(j+1,i+1,matrix[i][j]);
}

void ChessBoard::display(const QVector<QVector<char> > &board)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            cout<<board[i][j]<<" ";

        cout<<"\n";
    }
    cout<<"\n";
}
QVector< QVector<QVector<char> > > ChessBoard::generateMoves(QVector<QVector<char> > board,int depth)
{
    //maximise for black piece - small letters - depth is even
    //minimise for white piece - capital letters - depth is odd
    Piece p;
    QVector< QVector<QVector<char> > > boardStates;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {   char ch= (depth%2==0) ? toupper(board[i][j]):board[i][j];
            switch(ch)
            {
                case 'P': p.pawn.allMoves(board,boardStates,i,j); break;
                case 'N': p.knight.allMoves(board,boardStates,i,j); break;
                case 'B': p.bishop.allMoves(board,boardStates,i,j); break;
                case 'R': p.rook.allMoves(board,boardStates,i,j); break;
                case 'Q': p.queen.allMoves(board,boardStates,i,j); break;
                case 'K': p.king.allMoves(board,boardStates,i,j); break;
                default: break;
            }
        }
    }
    return boardStates;
}
QVector<QVector<char> > ChessBoard::minimax(QVector<QVector<char> > board,int depth)
{
    //base case
    if(depth==DEPTH)
    {
        //cout<<"DEPTH "<<DEPTH<<"========================Returning board\n";
        return board;
    }

    //cout<<"DEPTH "<<depth<<"============================\n";
    //cout<<"Generating moves===================\n";
    Piece p;
    QVector< QVector<QVector<char> > > boardStates=generateMoves(board,depth); //cout<<"Number of States: "<<boardStates.size()<<'\n';
    int minimizing=depth%2;
    int val=!minimizing?INT_MIN:INT_MAX; //maximise for even levels and minimise for odd levels
    QVector<QVector<char> > nextBoardState,resultBoardState; int nextBoardStateScore;
    for(int i=0;i<boardStates.size();i++)
    {
        nextBoardState=minimax(boardStates[i],depth+1);
        nextBoardStateScore=p.calculateScore(nextBoardState);
        if(!minimizing && nextBoardStateScore>val)
        {
            val=nextBoardStateScore;
            resultBoardState=boardStates[i];
        }
        else if(minimizing && nextBoardStateScore<val)
        {
            val=nextBoardStateScore;
            resultBoardState=boardStates[i];
        }
    }
    //cout<<"END OF DEPTH "<<depth<<"============================\n";
    return resultBoardState;
}
void ChessBoard::AIMove()
{
    //display(m_boardData);
    QVector<QVector<char> > result=minimax(m_boardData,0);
    //display(result);
    QVector<QVector<int> > m(2,QVector<int>(2,-1)); int index=0;
    for (int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(m_boardData[i][j] != result[i][j])
                m[index++]={i,j};
        }
    }

    //cout<<index<<"\n";
    //cout<<m[0][0]<<" "<<m[0][1]<<" \t "<<m[1][0]<<" "<<m[1][1]<<"\n";
    if(result[m[0][0]][m[0][1]]==' ')
    {
        //move board[m[0][0]][m[0][1]] to board[m[1][0]][m[1][1]]
        setData(m[1][1]+1,m[1][0]+1,data(m[0][1]+1,m[0][0]+1));
        setData(m[0][1]+1, m[0][0]+1, ' ');
    }
    else if(result[m[1][0]][m[1][1]]==' ')
    {
        //move board[m[1][0]][m[1][1]] to board[m[0][0]][m[0][1]]
        setData(m[0][1]+1,m[0][0]+1,data(m[1][1]+1,m[1][0]+1));
        setData(m[1][1]+1,m[1][0]+1,' ');
    }

}
