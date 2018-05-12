#include "buttonwidget.h"

ButtonWidget::ButtonWidget(const QStringList &texts, QWidget *parent)
    : QWidget(parent)
{
    signalMapper = new QSignalMapper(this);

    QGridLayout *gridLayout = new QGridLayout;

    for (int i = 0; i < texts.size(); ++i) {
            QPushButton *button = new QPushButton(texts[i]);
            connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(button, texts[i]);
            gridLayout->addWidget(button, i / 9, i % 9);
        }


    connect(signalMapper, SIGNAL(mapped(QString)),this, SIGNAL(clicked(QString)));

    setLayout(gridLayout);
}
