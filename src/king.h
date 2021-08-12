#ifndef KING_H
#define KING_H

#include "pieces.h"
#include "utils.h"

class King: public Piece
{
    public:
        King(char l, int s):Piece(l,s)
        { }
        Piece * clone() const
        {
            return new King(*this);
        }
        bool isValid(const QVector<QVector<Piece*> > &board,int init_row, int init_col, int dest_row, int dest_col)
        {
            //if initial square is empty return false
            if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
                return false;

            int diff1 = abs(dest_row - init_row);
            int diff2 = abs(dest_col - init_col);

            if( (diff1==1 && diff2==1) ||	(diff1==0 && diff2==1) ||	(diff1==1 && diff2==0) )
            {
                if(!isEmpty(board,dest_row,dest_col))
                {
                    return isDifferentColor(board,init_row,init_col,dest_row,dest_col);
                }
                return true;
            }
            return false;
        }
        void allMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates, int init_row, int init_col)
        {
            QVector<int> dx={-1,-1,-1, 0, 1, 1, 1, 0};
            QVector<int> dy={-1, 0, 1, 1, 1, 0,-1, 1};
            for(int di=0;di<8;di++)
            {
                if(!isOutofRange(init_row+dx[di],init_col+dy[di]) && isValid(board,init_row,init_col,init_row+dx[di],init_col+dy[di]) )
                {
                    addMove(board,boardStates,init_row,init_col,init_row+dx[di],init_col+dy[di]);
                }
            }
        }
};
#endif // KING_H
