#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include "pieces.h"

class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
    explicit ChessBoard(int ranks,int columns, QObject *parent = nullptr);
    void setData(int column, int rank, char value);
    int ranks();
    int columns();
    char data(int col,int rank) const;
    //void setFen(const QString &fen);
    void setFen(const QVector<QVector<char> > &matrix);
    void movePiece(int fromColumn, int fromRank, int toColumn, int toRank);
    bool movePieceUtil(int fromColumn, int fromRank, int toColumn, int toRank);
    QVector<QVector<char> > m_boardData;
private:
    int m_ranks, m_columns;
    Piece piece;
    void AIMove();
    void display(const QVector<QVector<char> > &board);
    QVector< QVector<QVector<char> > > generateMoves(QVector<QVector<char> > board,int depth);
    QVector<QVector<char> > minimax(QVector<QVector<char> > board,int depth);
protected:
    void setRanks(int newRanks);
    void setColumns(int newColumns);
    void initBoard();
    bool setDataInternal(int column, int rank, char value);

signals:
    void ranksChanged(int);
    void columnsChanged(int);
    void boardReset();
    void dataChanged(int column, int rank);
};

#endif // CHESSBOARD_H
