#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H
#include "chessboard.h"
#include "chessview.h"
#include <QObject>

class ChessAlgorithm : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Result result READ result)
    Q_PROPERTY(Player currentPlayer
               READ currentPlayer
               NOTIFY currentPlayerChanged)
public:
    explicit ChessAlgorithm(QObject *parent = nullptr);
    ChessBoard* board() const;
    void AIMove();
    QVector< QVector<QVector<Piece*> > > generateMoves(QVector<QVector<Piece*> >& board,int depth);
    QVector<QVector<Piece*> > minimax(QVector<QVector<Piece*> > board,int depth, int& alpha, int& beta);

    enum Result { NoResult, Player1Wins, Draw, Player2Wins };
    Q_ENUM(Result)
    enum Player { NoPlayer, Player1, Player2 };
    Q_ENUM(Player)
    inline Result result() const {
        return m_result;
    }
    inline Player currentPlayer() const {
        return m_currentPlayer;
    }

public slots:
    virtual void newGame();
    //virtual bool move(int colFrom, int rankFrom, int colTo, int rankTo);
    //bool move(const QPoint &from, const QPoint &to);

protected:
    virtual void setupBoard();
    void setBoard(ChessBoard *board);
    void setResult(Result);
    void setCurrentPlayer(Player);
    Result m_result;
    Player m_currentPlayer;

private:
    ChessBoard* m_board;

signals:
    void boardChanged(ChessBoard*);
    void gameOver(Result);
    void currentPlayerChanged(Player);

};

#endif // CHESSALGORITHM_H
