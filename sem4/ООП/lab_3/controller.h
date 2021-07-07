#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include <QTextEdit>
#include <QDebug>
#include "config.h"

class Controller : public QObject
{
    Q_OBJECT
    enum controller_state
    {
        FREE,
        BUSY
    };

public:
    explicit Controller(QObject *parent = nullptr);
    void set_new_target(int floor);
    void set_consol(QTextEdit *text);

signals:
    void set_target(int floor);

public slots:
    void achieved_floor(int floor);
    void passed_floor(int floor, direction direct);

private:
    int current_floor;

    bool targets[FLOORS_NUMBERS];

    controller_state current_state;
    direction current_direction;

    bool next_target(int &floor);

    QTextEdit *consol;
};

#endif // CONTROLLER_H
