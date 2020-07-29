#include "chessview.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
ChessView::ChessView(QWidget *parent) : QWidget(parent)
{
    m_selectedField=NULL;
    countMouseRelease=0;
}

void ChessView::setBoard(ChessBoard *board)
{

    if(m_board == board) {
    return;
    }

    m_board = board;
    // connect signals
    if(board) {
        connect(board, SIGNAL(dataChanged(int,int)),
                this, SLOT(update()));
        connect(board, SIGNAL(boardReset()),
                this, SLOT(update()));
    }
    updateGeometry();
}

ChessBoard* ChessView::board() const {
    return m_board;
}

void ChessView::setFieldSize(QSize arg)
{

    if (m_fieldSize == arg) {
        return;
    }
    m_fieldSize = arg;
    emit fieldSizeChanged(arg);
    updateGeometry();
}
QSize ChessView::fieldSize()
{
    return m_fieldSize;
}
QSize ChessView::sizeHint() const
{
    if(!m_board) {
        return QSize(100,100);
    }
    QSize boardSize = QSize(m_fieldSize.width()* m_board->columns() + 1,
                            m_fieldSize.height() * m_board->ranks() + 1);
    // 'M' is the widest letter
    int rankSize = fontMetrics().horizontalAdvance('M') + 4;
    int columnSize = fontMetrics().height() + 4;
    return boardSize + QSize(rankSize, columnSize);
}
QRect ChessView::fieldRect(int column, int rank) const
{
    if(!m_board) {
        return QRect();
    }
    const QSize fs = m_fieldSize;
    QPoint topLeft((column - 1) * fs.width(),
                   (rank - 1) * fs.height());

    QRect fRect = QRect(topLeft, fs);

    // offset rect by rank symbols
    int offset = fontMetrics().horizontalAdvance('M');
    return fRect.translated(offset+4, 0);
}

// function to draw the labels of each row, column and color the grid
void ChessView::paintEvent(QPaintEvent *)
{
    if(!m_board) {
        return;
    }
    QPainter painter(this);
    for(int r = m_board->ranks(); r > 0; --r) {
        painter.save();
        drawRank(&painter, r);
        painter.restore();
    }
    for(int c = 1; c <= m_board->columns(); ++c) {
        painter.save();
        drawColumn(&painter, c);
        painter.restore();
    }
    for(int r = 1; r <= m_board->ranks(); ++r) {
        for(int c = 1; c <= m_board->columns(); ++c) {
            painter.save();
            drawField(&painter, c, r);
            painter.restore();
        }
    }

    //Highlight the piece
    drawHighlights(&painter);
    for(int r =1; r<= m_board->ranks(); r++) {
        for(int c = 1; c <= m_board->columns(); ++c) {
            drawPiece(&painter, c, r);
        }
    }
}

//function to draw the labels for each row
void ChessView::drawRank(QPainter *painter, int rank)
{
    QRect r = fieldRect(1, rank);
    QRect rankRect = QRect(0, r.top(), r.left(), r.height()).adjusted(2, 0, -2, 0);
    QString rankText = QString::number(rank);
    painter->drawText(rankRect,
    Qt::AlignVCenter | Qt::AlignRight, rankText);
}

//function to draw the labels for each column
void ChessView::drawColumn(QPainter *painter, int column)
{
    QRect r = fieldRect(column, 1);
    QRect columnRect =QRect(r.left(), r.bottom(), r.width(), height() - r.bottom()).adjusted(0, 2, 0, -2);
    painter->drawText(columnRect,
    Qt::AlignHCenter | Qt::AlignTop, QChar('a' + column - 1));
}

//function to color the grid
void ChessView::drawField(QPainter *painter, int column, int rank)
{
    QBrush b;
    QRect rect = fieldRect(column, rank);
    painter->setPen(palette().color(QPalette::Dark));
    if((column+rank)%2 ==0)
        b=QColor("#CD853F");  //dark
    else
        b=QColor("#FFDEAD");   //light

    painter->setBrush(b);
    painter->drawRect(rect);
}
void ChessView::setPiece(char type, const QIcon &icon)
{
    m_pieces.insert(type, icon);
    update();
}
QIcon ChessView::piece(char type) const
{
    return m_pieces.value(type, QIcon());
}

// function to draw the piece on the colored grid
void ChessView::drawPiece(QPainter *painter, int column, int rank)
{

    QRect rect = fieldRect(column, rank);
    char value = m_board->data(column, rank);
    if(value != ' ') {
        QIcon icon = piece(value);
        if(!icon.isNull()) {
            icon.paint(painter, rect, Qt::AlignCenter);
        }
    }
}
//fieldAt() transforms
//a point in the widget coordinate space to the column and rank index
//of a field the point is contained in.
QPoint ChessView::fieldAt(const QPoint &pt) const
{
    if(!m_board) {
        return QPoint();
    }
    const QSize fs = m_fieldSize;
    int offset = fontMetrics().horizontalAdvance('M') + 4;
    // 'M' is the widest letter
    if(pt.x() < offset) {
        return QPoint();
    }
    int c = (pt.x() - offset) / fs.width();
    int r = pt.y() / fs.height();

    if(c < 0 || c >= m_board->columns() ||
       r < 0 || r >= m_board->ranks()) {
        return QPoint();
    }
    return QPoint(c+1,r+1);
}

//pass fieldAt() the position read from the QMouseEvent object. If the returned
//point is invalid, we quietly return from the method. Otherwise,
//clicked() is emitted with the obtained column and rank values.
void ChessView::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pt = fieldAt(event->pos());
    if(pt.isNull()) {
        return;
    }
    emit clicked(pt);
}
void ChessView::addHighlight(ChessView::Highlight *hl) {
    m_highlights.append(hl);
    update();
}
void ChessView::removeHighlight(ChessView::Highlight *hl) {
    m_highlights.removeOne(hl);
    update();
}
void ChessView::drawHighlights(QPainter *painter)
{
    for(int idx = 0; idx < highlightCount(); ++idx) {
        Highlight *hl = highlight(idx);
        if(hl->type() == FieldHighlight::Type) {
            FieldHighlight *fhl = static_cast<FieldHighlight*>(hl);
            QRect rect = fieldRect(fhl->column(), fhl->rank());
            painter->setPen(QPen(QColor(0,255,0),5));
            painter->drawRect(rect);
        }
    }
}
