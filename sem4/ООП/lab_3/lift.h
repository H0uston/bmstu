#ifndef LIFT_H
#define LIFT_H

#include <QObject>
#include <QTextEdit>
#include "cabin.h"
#include "controller.h"

class Lift : public QObject
{
    Q_OBJECT

public:
    Lift();
    void set_consol(QTextEdit *text);
    void add_stop(int floor);

private:
    QTextEdit *consol;
    Controller controller;
    Cabin cabin;
};

#endif // LIFT_H
