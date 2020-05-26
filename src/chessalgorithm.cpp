#include "chessalgorithm.h"
#include "chessboard.h"
#include "chessview.h"

ChessAlgorithm::ChessAlgorithm(QObject *parent) : QObject(parent)
{
    m_board=NULL;
    m_currentPlayer=NoPlayer;
    m_result=NoResult;
}

ChessBoard* ChessAlgorithm::board() const
{
    return m_board;
}

void ChessAlgorithm::setBoard(ChessBoard *board)
{
    if(board == m_board) {
    return;
    }
    delete m_board;
    m_board = board;
    emit boardChanged(m_board);
}

void ChessAlgorithm::setupBoard()
{
    setBoard(new ChessBoard(8, 8, this));
}

void ChessAlgorithm::newGame()
{
    setupBoard();
    QVector<QVector<char> > matrix(8,QVector<char>(8,' '));
    matrix[0]={' ','n','b','q','k','b','n','r'};    //black pieces
    matrix[1]={'p','p','p','p','p','p','p','p'};
    matrix[6]={'P','P','P','P','P','P','P','P'};    //white pieces
    matrix[7]={'R','N','B','Q','K','B','N','R',};
    board()->setFen(matrix);
}
void ChessAlgorithm::setResult(Result value)
{
    if(result() == value)
        return;


    if(result() == NoResult) {
        m_result = value;
        emit gameOver(m_result);
    } else {
        m_result = value;
    }
}
void ChessAlgorithm::setCurrentPlayer(Player value)
{
    if(currentPlayer() == value)
        return;

    m_currentPlayer = value;
    emit currentPlayerChanged(m_currentPlayer);
}
//not sure if this is necessary
/*bool ChessAlgorithm::move(const QPoint &from, const QPoint &to)
{
    //setCurrentPlayer(currentPlayer() == Player1 ? Player2 : Player1);
    return move(from.x(), from.y(), to.x(), to.y());
}*/

