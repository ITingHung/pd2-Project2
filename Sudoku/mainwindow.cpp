#include <QDebug>
#include <QVector>

#include "mainwindow.h"
#include "ui_mainwindow.h"

Sudoku su;
Sudoku su_status;
int constbuttonnum;
bool color = false;
int zero_map[81];
bool customize = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);

//Setup 81 Sudoku button
    for(int i=0;i<81;i++)
    {
        button[i] = new QPushButton(this);
        button[i]->setGeometry(QRect(QPoint(80*(i%9),80*(i/9)),QSize(80,80)));

        signalMapper_forbu = new QSignalMapper(this);
        connect(button[i], SIGNAL(clicked()), signalMapper_forbu, SLOT(map()));
        signalMapper_forbu->setMapping(button[i],i);
        connect(signalMapper_forbu,SIGNAL(mapped(int)), this, SLOT(clickedslot(int)));

        QPalette palin;
        palin.setColor(QPalette::Button, QColor(Qt::gray));
        if (i%9==3 || i%9==4 || i%9==5)
        {
            if(i<27 || i>54)
            {
                button[i]->setPalette(palin);
            }
        }
        if (i/9==3 || i/9==4 || i/9==5)
        {
            if(i%9==0 || i%9==1 || i%9==2 || i%9==6 || i%9==7 || i%9==8)
            {
                button[i]->setPalette(palin);
            }
        }

    }

    QFont font;
    font.setPointSize(20);

//Setup 5 level button
    for(int i=0;i<6;i++)
    {
        levelbu[i] = new QPushButton(this);
        levelbu[i]->setGeometry(QRect(QPoint(800,80+80*(i)),QSize(150,40)));
        levelbu[i]->setFont(font);

        signalMapper_forle = new QSignalMapper(this);
        connect(levelbu[i], SIGNAL(clicked()), signalMapper_forle, SLOT(map()));
        signalMapper_forle->setMapping(levelbu[i],i);
        connect(signalMapper_forle,SIGNAL(mapped(int)), this, SLOT(lebu_clickedslot(int)));
    }
    levelbu[0]->setText("Level 1");
    levelbu[1]->setText("Level 2");
    levelbu[2]->setText("Level 3");
    levelbu[3]->setText("Level 4");
    levelbu[4]->setText("Level 5");
    levelbu[5]->setText("Customize");

    for(int i=0;i<2;i++)
    {
        custobu[i] = new QPushButton(this);
        custobu[i]->setGeometry(QRect(QPoint(800+i*80,540),QSize(70,40)));
        custobu[i]->setFont(font);
    }
    custobu[0]->setText("O");
    custobu[1]->setText("X");

    for(int i=0;i<2;i++)
    {
        ansbu[i] = new QPushButton(this);
        ansbu[i]->setGeometry(QRect(QPoint(1000,80+80*(i)),QSize(200,40)));
        ansbu[i]->setFont(font);
    }
    ansbu[0]->setText("Check");
    ansbu[1]->setText("Show Answer");

    connect(ansbu[0], SIGNAL(clicked()), this, SLOT(checkslot()));
    connect(ansbu[1], SIGNAL(clicked()), this, SLOT(showansslot()));

    for(int i=0;i<2;i++)
    {
        setbu[i] = new QPushButton(this);
        setbu[i]->setGeometry(QRect(QPoint(1000,80+120*(i+2)),QSize(200,80)));

        QFont font;
        font.setPointSize(20);
        setbu[i]->setFont(font);
    }
    setbu[0]->setText("Start");
    setbu[1]->setText("Stop");

    connect(setbu[0], SIGNAL(clicked()), this, SLOT(startslot()));
    connect(setbu[1], SIGNAL(clicked()), this, SLOT(stopslot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickedslot(int buttonnum)
{
    set_iniColor();
    constbuttonnum = buttonnum;
    if(su_status.getElement(buttonnum)!=1)
    {
        QPalette buttonstatus;
        buttonstatus.setColor(QPalette::Button, QColor(Qt::darkCyan));
        button[buttonnum]->setPalette(buttonstatus);
        color = true;
    }
}

void MainWindow::lebu_clickedslot(int lebunum)
{
    customize = false;

    //Setup the whole map tp 0
    for(int i=0; i<81; ++i)
    {
        zero_map[i] = 0;
        button[i]->setText("");
        su_status.setElement(i,0);
    }
    su.SetMap(zero_map);

    //Set up the level button status
    QPalette levelstatus;
    levelstatus.setColor(QPalette::Button, QColor(Qt::white));
    for(int i=0; i<5; ++i)
    {
        levelbu[i]->setPalette(levelstatus);
    }
    levelstatus.setColor(QPalette::Button, QColor(Qt::yellow));
    levelbu[lebunum]->setPalette(levelstatus);

    if (lebunum == 0)
    {
        setBuEle(4,"8"); setBuEle(6,"6");
        setBuEle(11,"4");setBuEle(14,"7");setBuEle(17,"3");
        setBuEle(19,"5");setBuEle(20,"3");setBuEle(26,"2");setBuEle(27,"7");
        setBuEle(30,"2");setBuEle(31,"5");setBuEle(33,"4");setBuEle(34,"9");
        setBuEle(48,"1");setBuEle(49,"3");setBuEle(51,"7");setBuEle(52,"5");
        setBuEle(55,"7");setBuEle(56,"1");setBuEle(62,"5");setBuEle(63,"2");
        setBuEle(65,"8");setBuEle(68,"5");setBuEle(71,"1");
        setBuEle(76,"6");setBuEle(78,"9");
    }
    if (lebunum == 1)
    {
        setBuEle(1,"2"); setBuEle(6,"4");
        setBuEle(11,"7");setBuEle(12,"8");setBuEle(14,"9");setBuEle(17,"2");
        setBuEle(20,"1");setBuEle(22,"8");setBuEle(27,"5");
        setBuEle(28,"9");setBuEle(31,"3");setBuEle(32,"7");setBuEle(33,"8");
        setBuEle(38,"5");setBuEle(44,"4");
        setBuEle(49,"1");setBuEle(50,"4");setBuEle(51,"5");setBuEle(54,"9");
        setBuEle(55,"7");setBuEle(60,"1");setBuEle(62,"5");
        setBuEle(65,"4");setBuEle(68,"2");setBuEle(70,"7");setBuEle(71,"1");
        setBuEle(76,"4");setBuEle(81,"3");
    }
    if (lebunum == 2)
    {
        setBuEle(1,"5"); setBuEle(4,"3");setBuEle(7,"4");setBuEle(9,"1");
        setBuEle(11,"2");setBuEle(18,"8");
        setBuEle(22,"6");
        setBuEle(28,"1");setBuEle(30,"4");setBuEle(31,"7");setBuEle(36,"2");
        setBuEle(37,"8");setBuEle(41,"3");setBuEle(45,"6");
        setBuEle(46,"3");setBuEle(51,"8");setBuEle(52,"1");setBuEle(54,"4");
        setBuEle(60,"9");
        setBuEle(64,"4");setBuEle(71,"8");
        setBuEle(73,"6");setBuEle(75,"8");setBuEle(78,"2");setBuEle(81,"3");
    }
    if (lebunum == 4)
    {
        setBuEle(2,"9"); setBuEle(6,"5");setBuEle(7,"6");setBuEle(8,"1");setBuEle(9,"3");
        setBuEle(14,"7");setBuEle(18,"2");
        setBuEle(19,"5");setBuEle(24,"1");setBuEle(26,"4");setBuEle(27,"8");
        setBuEle(31,"5");setBuEle(33,"6");setBuEle(35,"2");
        setBuEle(41,"1");
        setBuEle(47,"1");setBuEle(49,"2");setBuEle(51,"3");
        setBuEle(55,"1");setBuEle(56,"3");setBuEle(58,"7");setBuEle(63,"9");
        setBuEle(64,"6");setBuEle(68,"5");
        setBuEle(73,"8");setBuEle(74,"2");setBuEle(75,"5");setBuEle(76,"1");setBuEle(80,"6");
    }
    if (lebunum == 5)
    {
        customize = true;
    }
}

void MainWindow::setBuEle(int buttonnum, QString numshow)
{
    QFont font;
    font.setPointSize(25);
    font.setBold(true);
    button[buttonnum-1]->setFont(font);

    int numinsu = numshow.toInt();
    su.setElement(buttonnum-1,numinsu);
    su_status.setElement(buttonnum-1,1);
    button[buttonnum-1]->setText(numshow);
}

void MainWindow::checkslot()
{
    QPalette pal;
    if(su.isCorrect())
    {
       pal.setColor(QPalette::Button, QColor(Qt::green));
       ansbu[0]->setPalette(pal);
       ansbu[0]->setText("Correct");
    }
    else
    {
        pal.setColor(QPalette::Button, QColor(Qt::red));
        ansbu[0]->setPalette(pal);
        ansbu[0]->setText("Incorrect");
    }

}

void MainWindow::showansslot()
{
    //Noice:if user key in the wrong number
    if(su.check_and_generate_info())
    {
        vector<int> empty_row_list;
        vector<int> empty_col_list;
        int unknown_num = su.get_empty_num(empty_row_list, empty_col_list);
        su.runKernel(0, unknown_num, empty_row_list, empty_col_list);

        QFont font;
        font.setPointSize(20);

        for (int i=0; i<81; ++i)
        {
            if(!su_status.getElement(i))
            {
                button[i]->setText(QString::number(su.getElement(i)));
                button[i]->setFont(font);
            }
        }
    }
}

void MainWindow::startslot()
{
    QPalette inistatus,setstatus,warn,correct;
    inistatus.setColor(QPalette::Button, QColor(Qt::white));
    setstatus.setColor(QPalette::Button, QColor(Qt::blue));
    warn.setColor(QPalette::Button, QColor(Qt::red));
    correct.setColor(QPalette::Button, QColor(Qt::green));
    ansbu[0]->setPalette(inistatus);
    ansbu[0]->setText("Check");
    setbu[0]->setPalette(setstatus);
    setbu[1]->setPalette(inistatus);

    //Check if the customize question is solvable
    if(customize)
    {
        if(!su.check_and_generate_info())
        {
            custobu[0]->setPalette(inistatus);
            custobu[1]->setPalette(warn);
            setbu[0]->setPalette(inistatus);
        }
        else
        {
            custobu[0]->setPalette(correct);
            custobu[1]->setPalette(inistatus);
            customize = false;
            //Fix all the customize button when Start
            for (int i=0; i<81; ++i)
            {
                if (su_status.getElement(i)==2)
                    su_status.setElement(i,1);
            }
        }
    }
}

void MainWindow::stopslot()
{
    QPalette inistatus,setstatus;
    inistatus.setColor(QPalette::Button, QColor(Qt::white));
    setstatus.setColor(QPalette::Button, QColor(Qt::blue));
    setbu[0]->setPalette(inistatus);
    setbu[1]->setPalette(setstatus);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(color)
    {
        QFont font;
        font.setPointSize(20);
        button[constbuttonnum]->setFont(font);
        if(customize)
        {
            font.setPointSize(25);
            font.setBold(true);
            button[constbuttonnum]->setFont(font);
            su_status.setElement(constbuttonnum,2);
        }

        if(event->key()==Qt::Key_1)
        {
            button[constbuttonnum]->setText("1");
            su.setElement(constbuttonnum,1);
        }
        if(event->key()==Qt::Key_2)
        {
            button[constbuttonnum]->setText("2");
            su.setElement(constbuttonnum,2);
        }
        if(event->key()==Qt::Key_3)
        {
            button[constbuttonnum]->setText("3");
            su.setElement(constbuttonnum,3);
        }
        if(event->key()==Qt::Key_4)
        {
            button[constbuttonnum]->setText("4");
            su.setElement(constbuttonnum,4);
        }
        if(event->key()==Qt::Key_5)
        {
            button[constbuttonnum]->setText("5");
            su.setElement(constbuttonnum,5);
        }
        if(event->key()==Qt::Key_6)
        {
            button[constbuttonnum]->setText("6");
            su.setElement(constbuttonnum,6);
        }
        if(event->key()==Qt::Key_7)
        {
            button[constbuttonnum]->setText("7");
            su.setElement(constbuttonnum,7);
        }
        if(event->key()==Qt::Key_8)
        {
            button[constbuttonnum]->setText("8");
            su.setElement(constbuttonnum,8);
        }
        if(event->key()==Qt::Key_9)
        {
            button[constbuttonnum]->setText("9");
            su.setElement(constbuttonnum,9);
        }

        color = false;
        set_iniColor();
    }
}

 void MainWindow::set_iniColor()
 {
     QPalette pal;
     pal.setColor(QPalette::Button, QColor(Qt::white));
     button[constbuttonnum]->setPalette(pal);
     if (constbuttonnum%9==3 || constbuttonnum%9==4 || constbuttonnum%9==5)
     {
         if(constbuttonnum<27 || constbuttonnum>54)
         {
             pal.setColor(QPalette::Button, QColor(Qt::gray));
             button[constbuttonnum]->setPalette(pal);
         }
     }
     if (constbuttonnum/9==3 || constbuttonnum/9==4 || constbuttonnum/9==5)
     {
         if(constbuttonnum%9==0 || constbuttonnum%9==1 || constbuttonnum%9==2 || constbuttonnum%9==6 || constbuttonnum%9==7 || constbuttonnum%9==8)
         {
             pal.setColor(QPalette::Button, QColor(Qt::gray));
             button[constbuttonnum]->setPalette(pal);
         }
     }
 }
