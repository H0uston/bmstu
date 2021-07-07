#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QString>
#include "config.h"
#include "doors.h"

class Cabin : public QObject
{
    Q_OBJECT
    enum cabin_state
    {
        MOVING,
        GOT_TARGET,
        ON_HOLD
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    void set_consol(QTextEdit *text);

signals:
    void start_moving();
    void passing_floor(int floor, direction direct);
    void reached_target_floor(int floor);
    void cabin_stopped(int floor);

public slots:
    void cabin_moving();
    void cabin_stopping();
    void cabin_set_target(int floor);

private:
    int current_floor;
    int target_floor;

    cabin_state current_state;
    direction current_direction;

    Doors doors;

    QTimer moving_one_floor_timer;
    QTextEdit *consol;
};


#endif // CABIN_H
