#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessalgorithm.h"
#include "chessview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void viewClicked(const QPoint &field);
//    void play();

    ChessView *m_view;
    ChessAlgorithm *m_algorithm;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPoint m_clickPoint;

};
#endif // MAINWINDOW_H
