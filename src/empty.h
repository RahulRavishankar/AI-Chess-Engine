#ifndef EMPTY_H
#define EMPTY_H

#include "pieces.h"
#include "utils.h"

class Empty: public Piece
{
    public:
        Empty(char l, int s):Piece(l,s)
        { }
        Piece * clone() const
        {
            return new Empty(*this);
        }
        bool isValid(const QVector<QVector<Piece*> > &, int, int, int, int)
        {
            // always false
            return false;
        }
        void allMoves(QVector<QVector<Piece*> > &, QVector< QVector<QVector<Piece*> > > &, int, int)
        { cout<<"No moves for an empty square\n"; }
};
#endif // EMPTY_H
