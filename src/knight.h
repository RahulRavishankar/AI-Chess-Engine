#ifndef KNIGHT_H
#define KNIGHT_H

#include "pieces.h"
#include "utils.h"

class Knight: public Piece
{
    public:
        Knight(char l, int s):Piece(l,s)
        { }
        Piece * clone() const
        {
            return new Knight(*this);
        }
        bool isValid(const QVector<QVector<Piece*> > &board,int init_row, int init_col, int dest_row, int dest_col)
        {
            //if initial sqauare is empty return false
            if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
                return false;

            int diff1 = abs(dest_row - init_row);
            int diff2 = abs(dest_col - init_col);

            //if the move is L-shaped
            if ( (diff1 == 2 && diff2 == 1) || (diff1 == 1 && diff2 == 2) )
            {
                // if the destination cell is not empty
                if(!isEmpty(board,dest_row,dest_col))
                {
                    if(isDifferentColor(board,init_row,init_col,dest_row,dest_col))
                        return true;
                    else
                        return false;
                }
                return true;
            }

            return false;
        }
        void allMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates, int init_row, int init_col)
        {
            QVector<int> dx={-2,-1, 1, 2, 2, 1,-1,-2};
            QVector<int> dy={ 1, 2, 2, 1,-1,-2,-2,-1};
            for(int di=0;di<8;di++)
            {
                if(!isOutofRange(init_row+dx[di],init_col+dy[di]) && isValid(board,init_row,init_col,init_row+dx[di],init_col+dy[di]) )
                {
                    addMove(board,boardStates,init_row,init_col,init_row+dx[di],init_col+dy[di]);
                }
            }
        }
};

#endif // KNIGHT_H
