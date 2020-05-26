#ifndef CHESSVIEW_H
#define CHESSVIEW_H
#include "chessboard.h"
#include <QWidget>
#include <QPointer>
#include <QPainter>
#include <QMap>
#include <QIcon>

class ChessView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize fieldSize
    READ fieldSize WRITE setFieldSize NOTIFY fieldSizeChanged)
public:
    explicit ChessView(QWidget *parent = nullptr);
    void setBoard(ChessBoard *);
    void setFieldSize(QSize arg);
    void setPiece(char type, const QIcon &icon);
    QIcon piece(char type) const;
    ChessBoard* board() const;
    void mouseReleaseEvent(QMouseEvent *event);
    int countMouseRelease;
    class Highlight {
        public:
            Highlight() {}
            virtual ~Highlight() {}
            virtual int type() const { return 0; }
    };
    class FieldHighlight : public Highlight {
        public:
            enum { Type = 1 };
            FieldHighlight(int column, int rank, QColor color): m_field(column, rank), m_color(color) {}
            inline int column() const { return m_field.x(); }
            inline int rank() const { return m_field.y(); }
            inline QColor color() const { return m_color; }
            int type() const { return Type; }
        private:
            QPoint m_field;
            QColor m_color;
    };
    void addHighlight(Highlight *hl);
    void removeHighlight(Highlight *hl);
    inline Highlight *highlight(int index) const {
        return m_highlights.at(index);
    }
    inline int highlightCount() const {
        return m_highlights.size();
    }
    void drawHighlights(QPainter *painter);
    inline FieldHighlight* selectedField()
    {
        return m_selectedField;
    }
    FieldHighlight *m_selectedField;

private:
    QPointer<ChessBoard> m_board;
    QSize m_fieldSize;
    QSize sizeHint() const;
    QSize fieldSize();
    QRect fieldRect(int column, int rank) const;
    void paintEvent(QPaintEvent *);
    QMap<char, QIcon> m_pieces;
    QPoint fieldAt(const QPoint &pt) const;
    QList<Highlight*> m_highlights;

protected:
    virtual void drawRank(QPainter *painter, int r);
    virtual void drawColumn(QPainter *painter, int r);
    virtual void drawField(QPainter *painter, int c, int r);
    virtual void drawPiece(QPainter *painter, int c, int r);

signals:
    void fieldSizeChanged(QSize);
    void clicked(const QPoint &);
};

#endif // CHESSVIEW_H
