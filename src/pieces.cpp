#include "pieces.h"

Piece::operator char() const
{
    return label;
}

char Piece::getLabel() const
{
    return label;
}

int Piece::getScore() const
{
    return score;
}

Piece* Piece::clone() const
{
    return NULL;
}

bool Piece::isValid(const QVector<QVector<Piece*> >&,int, int, int, int)
{
    // always false
    return false;
}

void Piece::allMoves(QVector<QVector<Piece*> > &, QVector< QVector<QVector<Piece*> > >&, int, int)
{
    // do nothing
}

