#ifndef UTILS_H
#define UTILS_H
#include "pieces.h"

bool isEmpty(const QVector<QVector<Piece*> > &board, int dest_row, int dest_col);
bool isDifferentColor(const QVector<QVector<Piece*> > &board,int init_row, int init_col,
                      int dest_row, int dest_col);
int calculateScore(const QVector<QVector<Piece*> > &board);
bool isOutofRange(int row,int col);
void addMove(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates,
             int init_row, int init_col,int dest_row,int dest_col);
void generateAxialMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates,
                        int init_row, int init_col);
void generateDiagonalMoves(QVector<QVector<Piece*> > &board,QVector< QVector<QVector<Piece*> > > &boardStates,
                    int init_row, int init_col);
#endif // UTILS_H
