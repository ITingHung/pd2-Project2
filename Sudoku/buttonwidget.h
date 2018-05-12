#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QPushButton>
#include <QDebug>

class ButtonWidget : public QWidget
{
    Q_OBJECT

public:
    ButtonWidget(const QStringList &texts, QWidget *parent = 0);

signals:
    void clicked(const QString &text);

private:
    QSignalMapper *signalMapper;
};

#endif // BUTTONWIDGET_H
