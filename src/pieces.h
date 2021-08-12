#ifndef PIECES_H
#define PIECES_H

#include <iostream>
#include <map>
#include <QVector>
#include <QObject>
using namespace std;
#define PAWN 10   	//P
#define KNIGHT 30	//N
#define BISHOP 30	//B
#define ROOK 50		//R
#define QUEEN 90	//Q
#define KING 900	//K
#define EMPTY 0

class Piece: public QObject
{
    private:
        char label;
        int score;
    public:
        Piece()
        { }
        Piece(char l, int s):label(l), score(s)
        { }
        Piece(const Piece& other)
        :QObject(0)
        {
            label = other.label;
        }
        Piece& operator=(const Piece& rhs)
        {
            label = rhs.label;
            return *this;
        }
        virtual ~Piece() = default;

        operator char() const;
        char getLabel() const;
        int getScore() const;
        virtual Piece* clone() const;
        virtual bool isValid(const QVector<QVector<Piece*> >&,int, int, int, int);
        virtual void allMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > >&, int, int);
};

#endif
