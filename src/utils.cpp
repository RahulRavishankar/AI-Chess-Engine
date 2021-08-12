#include<iostream>
#include<QVector>
#include "pieces.h"
#include "chessboard.h"

bool isEmpty(const QVector<QVector<Piece*> > &board, int row, int col)
{
    return board[row][col]->getLabel()==' ';
}
bool isDifferentColor(const QVector<QVector<Piece*> > &board,int init_row, int init_col, int dest_row, int dest_col)
{
    if( (isupper(*board[init_row][init_col]) &&  islower(*board[dest_row][dest_col])) ||
        (islower(*board[init_row][init_col]) &&  isupper(*board[dest_row][dest_col])) )
        return true;

    return false;
}
bool isOutofRange(int row,int col)
{
  return !(row>=0 && row<8 && col>=0 && col<8);
}
int calculateScore(const QVector<QVector<Piece*> > &board)
{
    int score=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            // White pieces - Denoted by Capital letters - Minimise the score - negative sign
            // Black pieces - Denoted by Small letters - Maximise the score - positive sign
            int sign = ((isupper(*board[i][j]))?-1:1);
            score += board[i][j]->getScore() * sign;
        }
    }
    return score;
}
void addMove(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates,
            int init_row, int init_col,int dest_row,int dest_col)
{
    //move the piece
    board[dest_row][dest_col]=board[init_row][init_col];
    board[init_row][init_col]= ChessBoard::prototype[' ']->clone();

    //store the current board state
    boardStates.push_back(board);

    //move the piece back
    board[init_row][init_col]=board[dest_row][dest_col];
    board[dest_row][dest_col]=ChessBoard::prototype[' ']->clone();;
}
void generateAxialMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates,
                        int init_row, int init_col)
{
    int row,col;

    row=init_row; col=init_col+1;		//movement to the right
    while(col<8 && *board[row][col]==' ')
    {
        addMove(board,boardStates,init_row,init_col,row,col);
        col++;
    }
    row=init_row+1; col=init_col;		//downward movement
    while(row<8 && *board[row][col]==' ')
    {
        addMove(board,boardStates,init_row,init_col,row,col);
        row++;
    }
    row=init_row; col=init_col-1;		//movement to the left
    while(col>=0 && *board[row][col]==' ')
    {
        addMove(board,boardStates,init_row,init_col,row,col);
        col--;
    }
    row=init_row-1; col=init_col;		//upward movement
    while(row>=0 && *board[row][col]==' ')
    {
        addMove(board,boardStates,init_row,init_col,row,col);
        row--;
    }
}
void generateDiagonalMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates,
                        int init_row, int init_col)
{
    int row,col;

    row=init_row-1; col=init_col+1; 	//diagonal Right-Up
    while(row>=0 && col<8 && *board[row][col]==' ')
    {
        addMove(board,boardStates,init_row,init_col,row,col);
        row--; col++;
    }
    row=init_row+1; col=init_col+1;		//diagonal Right-Down
    while(row<8 && col<8 && *board[row][col]==' ')
    {
        addMove(board,boardStates,init_row,init_col,row,col);
        row++; col++;
    }
    row=init_row+1; col=init_col-1;		//diagonal Left-Down
    while(row<8 && col>=0 && *board[row][col]==' ')
    {
        addMove(board,boardStates,init_row,init_col,row,col);
        row++; col--;
    }
    row=init_row-1; col=init_col-1; 	//diagonal Left-Up
    while(row>=0 && col>=0 && *board[row][col]==' ')
    {
        addMove(board,boardStates,init_row,init_col,row,col);
        row--; col--;
    }
}
