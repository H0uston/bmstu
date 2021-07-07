#include "cabin.h"


Cabin::Cabin(QObject *parent) : QObject(parent)
{
    current_direction = STAY;
    current_floor = 1;
    current_state = ON_HOLD;

    moving_one_floor_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(reached_target_floor(int)), this, SLOT(cabin_stopping()));
    QObject::connect(this, SIGNAL(cabin_stopped(int)), &doors, SLOT(start_openning()));
    QObject::connect(&doors, SIGNAL(closeddoors()), this, SLOT(cabin_moving()));
    QObject::connect(&moving_one_floor_timer, SIGNAL(timeout()), this, SLOT(cabin_moving()));
    QObject::connect(this, SIGNAL(start_moving()), &doors, SLOT(start_closing()));
}

void Cabin::set_consol(QTextEdit *text)
{
    consol = text;
    doors.set_consol(text);
}

void Cabin::cabin_moving()
{
    if (current_state == GOT_TARGET)
    {
        if (current_floor == target_floor)
            emit reached_target_floor(current_floor);
        else
        {
            current_state = MOVING;
            moving_one_floor_timer.start(MOVING_ONE_FLOOR_TIME);
        }
    }
    if (current_state == MOVING)
    {
        if (current_direction == UP)
            current_floor += 1;
        else if (current_direction == DOWN)
            current_floor -= 1;

        if (current_floor == target_floor)
            emit reached_target_floor(current_floor);
        else
        {
            emit passing_floor(current_floor, current_direction);
            moving_one_floor_timer.start(MOVING_ONE_FLOOR_TIME);
        }
    }
}

void Cabin::cabin_stopping()
{
    current_state = ON_HOLD;
    moving_one_floor_timer.stop();
    consol->append("Лифт остановился на этаже " + QString::number(current_floor));
    emit cabin_stopped(current_floor);
}

void Cabin::cabin_set_target(int floor)
{
    current_state = GOT_TARGET;
    target_floor = floor;
    if (current_floor == target_floor)
        emit reached_target_floor(floor);
    else
    {
        if (current_floor > target_floor)
            current_direction = DOWN;
        else
            current_direction = UP;
        emit start_moving();
    }
}
