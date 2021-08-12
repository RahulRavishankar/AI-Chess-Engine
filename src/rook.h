#ifndef ROOK_H
#define ROOK_H

#include "pieces.h"
#include "utils.h"

class Rook: public Piece
{
    public:
        Rook(char l, int s):Piece(l,s)
        { }
        Piece * clone() const
        {
            return new Rook(*this);
        }
        bool isJump(const QVector<QVector<Piece*> > &board,int init_row, int init_col, int dest_row, int dest_col)
        {
            if(init_row==dest_row)
            {
                init_col=init_col+1*((init_col<dest_col)?1:-1);
                while(init_col!=dest_col && board[init_row][init_col]->getLabel()==' ')
                    init_col=init_col+1*((init_col<dest_col)?1:-1);

                if(init_col!=dest_col)  //found a piece along the way, cannot jump
                    return false;
            }
            else
            {
                init_row=init_row+1*((init_row<dest_row)?1:-1);
                while(init_row!=dest_row && board[init_row][init_col]->getLabel()==' ')
                    init_row=init_row+1*((init_row<dest_row)?1:-1);

                if(init_row!=dest_row)  //found a piece along the way, cannot jump
                    return false;

            }
            //reached the final dest, check if it's of different color
            if(isDifferentColor(board,init_row,init_col,dest_row,dest_col))
                return true;

            return false;
        }
        bool isValid(const QVector<QVector<Piece*> > &board,int init_row, int init_col, int dest_row, int dest_col)
        {
            //if initial sqauare is empty return false
            if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
                return false;

            int diff1 = abs(dest_row - init_row);
            int diff2 = abs(dest_col - init_col);

            if( (diff1==0 && diff2>0) || (diff1>0 && diff2==0) )
            {
                if(isJump(board,init_row,init_col,dest_row,dest_col))
                    return false;

                if(!isEmpty(board,dest_row,dest_col))
                {
                    if(isDifferentColor(board,init_row,init_col,dest_row,dest_col))
                        return true;

                    return false;
                }
                return true;
            }
            return false;
        }
        void allMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates, int init_row, int init_col)
        {
            generateAxialMoves(board,boardStates,init_row,init_col);
        }
};
#endif // ROOK_H
