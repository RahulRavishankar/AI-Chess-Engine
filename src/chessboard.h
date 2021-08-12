#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <unordered_map>

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
    QVector<QVector<Piece*> > getBoard() const;
    Piece* data(int col,int rank) const;
    //void setFen(const QString &fen);
    void setFen(const QVector<QVector<char> > &matrix);
    void movePiece(int fromColumn, int fromRank, int toColumn, int toRank);
    static unordered_map<char, Piece*> prototype;

private:
    QVector<QVector<Piece*> > m_boardData;
    int m_ranks, m_columns;
    void display() const;
    bool movePieceUtil(int fromColumn, int fromRank, int toColumn, int toRank);

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
