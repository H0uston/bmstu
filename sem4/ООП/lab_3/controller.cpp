#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    current_state = FREE;
    current_direction = STAY;
    current_floor = 0;
    for (int i = 0; i < FLOORS_NUMBERS; i++)
        targets[i] = false;
}

void Controller::set_new_target(int floor)
{
    current_state = BUSY;
    targets[floor - 1] = true;
    next_target(floor);
    emit set_target(floor);
}

void Controller::set_consol(QTextEdit *text)
{
    consol = text;
}

void Controller::achieved_floor(int floor)
{
    if (current_state == BUSY)
    {
        current_floor = floor;
        current_direction = STAY;
        targets[floor - 1] = false;
        if (next_target(floor))
            emit set_target(floor);
        else
            current_state = FREE;
    }
}

void Controller::passed_floor(int floor, direction direct)
{
    current_floor = floor;
    current_direction = direct;

    QString act = " ";
    if (direct == UP)
        act = "поднимается ";
    else if (direct == DOWN)
        act = "опускается ";

    int floor_1 = floor, floor_2 = 0;
    if (direct == UP)
        floor_2 = floor_1 + 1;
    else if (direct == DOWN)
        floor_2 = floor_1 - 1;

    consol->append("Лифт " + act + "между этажами "
                 + QString::number(floor_1) + " и " + QString::number(floor_2));

}

bool Controller::next_target(int &floor)
{
    int step = -1;

    if (current_direction == UP)
        step = 1;

    for (int i = current_floor; i <= FLOORS_NUMBERS && i > 0; i += step)
    {
        if (targets[i - 1])
        {
            floor = i;
            return true;
        }
    }

    step = -step;

    for (int i = current_floor; i <= FLOORS_NUMBERS && i > 0; i += step)
    {
        if (targets[i - 1])
        {
            floor = i;
            return true;
        }
    }

    return false;
}
