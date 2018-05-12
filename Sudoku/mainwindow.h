#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QSignalMapper>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QPalette>
#include <QKeyEvent>
#include <QTableWidget>
#include <QFont>

#include "Sudoku.h"
#include "buttonwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(const QStringList &texts, QWidget *parent);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);
    void setBuEle(int buttonnum, QString numshow);

public slots:
    void clickedslot(int buttonnum);
    void lebu_clickedslot(int lebunum);
    void checkslot();
    void showansslot();
    void startslot();
    void stopslot();

private slots:

private:
    void set_iniColor();
    Ui::MainWindow *ui;
    QPushButton *button[81];
    QPushButton *levelbu[6];
    QPushButton *custobu[2];
    QPushButton *ansbu[2];
    QPushButton *setbu[2];
    QSignalMapper *signalMapper_forbu;
    QSignalMapper *signalMapper_forle;
};

#endif // MAINWINDOW_H
