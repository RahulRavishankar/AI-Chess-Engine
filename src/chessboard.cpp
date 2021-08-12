#include <iostream>
#include <QDebug>
#include <unistd.h>
using namespace std;

#include "chessboard.h"
#include "pieces.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "empty.h"

unordered_map<char, Piece*> ChessBoard::prototype = {
    {'p', new Pawn('p',PAWN)},
    {'P', new Pawn('P',PAWN)},
    {'n', new Knight('n',KNIGHT)},
    {'N', new Knight('N',KNIGHT)},
    {'b', new Bishop('b',BISHOP)},
    {'B', new Bishop('B',BISHOP)},
    {'r', new Rook('r',ROOK)},
    {'R', new Rook('R',ROOK)},
    {'q', new Queen('q',QUEEN)},
    {'Q', new Queen('Q',QUEEN)},
    {'k', new King('k',KING)},
    {'K', new King('K',KING)},
    {' ', new Empty(' ',EMPTY)}
};

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
    m_boardData.resize(8);
    for(int i=0;i<8;++i){
        m_boardData[i] = *(new QVector<Piece*>(8));
        for(int j=0;j<8;++j) {
            m_boardData[i][j] = prototype[' ']->clone();
        }
    }

    emit boardReset();
}

Piece* ChessBoard::data(int column, int rank) const
{
    return m_boardData[rank-1][column-1];
}

bool ChessBoard::setDataInternal(int column, int rank, char value)
{
    if(*m_boardData[rank-1][column-1] == value) {
        return false;
    }
    delete m_boardData[rank-1][column-1];
    m_boardData[rank-1][column-1] = prototype[value]->clone();
    return true;
}

void ChessBoard::setData(int column, int rank, char value)
{
    if(rank-1<0 || rank-1>=m_ranks || column-1<0 || column-1>=m_columns) {
        cout<<"Invalid rank: "<<rank<<" and column: "<<column<<"\n";
        return;
    }

    if(setDataInternal(column, rank, value)) {
        emit dataChanged(column, rank);
    }
}

//utility function of movePiece to check if the move is valid
bool ChessBoard::movePieceUtil(int fromColumn, int fromRank, int toColumn, int toRank)
{
    return m_boardData[fromRank][fromColumn]->isValid(m_boardData,fromRank,fromColumn,toRank,toColumn);
}

//function to check if the move is valid, update the board if the move is valid
void ChessBoard::movePiece(int fromColumn, int fromRank, int toColumn, int toRank)
{
    if(movePieceUtil(fromColumn-1,fromRank-1,toColumn-1,toRank-1))
    {
        setData(toColumn, toRank, *data(fromColumn, fromRank));
        setData(fromColumn, fromRank, ' ');
    }
}
void ChessBoard::setFen(const QVector<QVector<char> > &matrix)
{
    for(int i=0;i<ranks();i++)
        for(int j=0;j<columns();j++)
            setDataInternal(j+1,i+1,matrix[i][j]);
}

void ChessBoard::display() const
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            cout<<(char)*m_boardData[i][j]<<" ";

        cout<<"\n";
    }
    cout<<"\n";
}

QVector<QVector<Piece*> > ChessBoard::getBoard() const
{
    return m_boardData;
}
