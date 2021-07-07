#include "lift.h"

Lift::Lift()
{
    QObject::connect(&controller, SIGNAL(set_target(int)), &cabin, SLOT(cabin_set_target(int)));
    QObject::connect(&cabin, SIGNAL(passing_floor(int,direction)), &controller, SLOT(passed_floor(int,direction)));
    QObject::connect(&cabin, SIGNAL(cabin_stopped(int)), &controller, SLOT(achieved_floor(int)));
}

void Lift::set_consol(QTextEdit *text)
{
    this->consol = text;
    controller.set_consol(text);
    cabin.set_consol(text);
}

void Lift::add_stop(int floor)
{
    controller.set_new_target(floor);
}
