#ifndef PAWN_H
#define PAWN_H
#include "pieces.h"
#include "utils.h"

class Pawn: public Piece
{
    public:
        Pawn(char l, int s):Piece(l,s)
        { }
        Piece * clone() const
        {
            return new Pawn(*this);
        }
        bool isValid(const QVector<QVector<Piece*> > &board,int init_row, int init_col, int dest_row, int dest_col)
        {
            //if initial sqauare is empty return false
            if(isEmpty(board,init_row,init_col) || isOutofRange(dest_row,dest_col))
                return false;

            int diff1 = dest_row - init_row;
            int diff2 = dest_col - init_col;

            //white pieces can't move backwards (Denoted by capital letter)
            if(board[init_row][init_col]->getLabel()>=65 && board[init_row][init_col]->getLabel()<91 && diff1>0)  //>
                return false;

            //black pieces can't move backwards (Denoted by small letter)
            if(board[init_row][init_col]->getLabel()>=97 && board[init_row][init_col]->getLabel()<123 && diff1<0)  //<
                return false;

            diff1=abs(diff1);
            diff2=abs(diff2);

            //out of bounds
            if (diff1> 2 || diff2 > 1 || (!diff1 && !diff2))
                return false;

            //move one step diagonally
            if (diff1==1 && diff2==1)
            {
                //Killing a piece via a pawn
                if(!isEmpty(board,dest_row,dest_col) && isDifferentColor(board,init_row,init_col,dest_row,dest_col) )
                    return true;

                return false;
            }

            //move one or two steps further if empty
            if(!isEmpty(board,dest_row,dest_col))
                return false;

            return true;
        }
        void allMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates, int init_row, int init_col)
        {
            //int count_moves=0; cout<<"number of moves=====\n";
            QVector<int> dx;
            if(board[init_row][init_col]->getLabel()=='p')	{
                dx={1,1, 1};
            }
            else{
                dx={-1,-1,-1};
            }
            QVector<int> dy={0,-1,1};

            for(int di=0;di<dx.size();di++)
            {
                if(!isOutofRange(init_row+dx[di],init_col+dy[di]) && isValid(board,init_row,init_col,init_row+dx[di],init_col+dy[di]) )
                {
                    addMove(board,boardStates,init_row,init_col,init_row+dx[di],init_col+dy[di]); //count_moves++;
                }

            }
        }
};

#endif // PAWN_H
