#ifndef CONFIG_H
#define CONFIG_H

#define FLOORS_NUMBERS 5

#define MOVING_ONE_FLOOR_TIME 4500
#define DOORS_MOVEMENT_TIME 3000
#define DOORS_STAY_OPEN_TIME 6000

enum direction
{
    UP = 1,
    DOWN = -1,
    STAY = 0
};

#endif // CONFIG_H
