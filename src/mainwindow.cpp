#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_view = new ChessView;
    m_algorithm = new ChessAlgorithm(this);

    m_algorithm->newGame();
    m_view->setBoard(m_algorithm->board());
    setCentralWidget(m_view);
    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_view->setFieldSize(QSize(90,90));

    m_view->setPiece('P', QIcon(":/resources/img/pawn1.png")); // pawn   //white
    m_view->setPiece('K', QIcon(":/resources/img/king1.png")); // king
    m_view->setPiece('Q', QIcon(":/resources/img/queen1.png")); // queen
    m_view->setPiece('R', QIcon(":/resources/img/rook1.png")); // rook
    m_view->setPiece('N', QIcon(":/resources/img/knight1.png")); // knight
    m_view->setPiece('B', QIcon(":/resources/img/bishop1.png")); // bishop

    m_view->setPiece('p', QIcon(":/resources/img/pawn.png")); // pawn   //black
    m_view->setPiece('k', QIcon(":/resources/img/king.png")); // king
    m_view->setPiece('q', QIcon(":/resources/img/queen.png")); // queen
    m_view->setPiece('r', QIcon(":/resources/img/rook.png")); // rook
    m_view->setPiece('n', QIcon(":/resources/img/knight.png")); // knight
    m_view->setPiece('b', QIcon(":/resources/img/bishop.png")); // bishop

    connect(m_view, &ChessView::clicked,this, &MainWindow::viewClicked);
}
void MainWindow::viewClicked(const QPoint &field)
{
    if(m_clickPoint.isNull()) {
        if(*m_view->board()->data(field.x(), field.y()) != ' ') {
            m_clickPoint = field;
            m_view->m_selectedField = new ChessView::FieldHighlight(field.x(), field.y(), QColor(255, 0, 0,100) );
            m_view->addHighlight(m_view->m_selectedField);
        }
    } else {
//        cout<<m_clickPoint.x()<<" "<<field.x()<<" "<<m_clickPoint.y()<<" "<<field.y()<<"\n";
        if(field != m_clickPoint && m_clickPoint.x()!=field.x() && m_clickPoint.y()!=field.y()) {
            m_view->board()->movePiece(
            m_clickPoint.x(), m_clickPoint.y(),
            field.x(), field.y() );
        }
        m_clickPoint = QPoint();
        m_view->removeHighlight(m_view->m_selectedField);
        delete m_view->m_selectedField;
        m_view->m_selectedField = nullptr;

       if(field != m_clickPoint && m_clickPoint.x()!=field.x() && m_clickPoint.y()!=field.y()) {
            m_algorithm->AIMove();
       }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

