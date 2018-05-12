#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //setting windows size
    QDesktopWidget wid;
    int screenW = 1300;
    int screenH = 720;
    w.setGeometry(wid.screen()->width()/2-(screenW/2), wid.screen()->height()/2 - (screenH/2), screenW, screenH);
    //setting windows title
    w.setWindowTitle("Sudoku");
    w.setFixedSize(screenW, screenH);

    w.show();
    return a.exec();
}
