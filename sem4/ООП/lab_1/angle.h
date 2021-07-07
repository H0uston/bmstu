#ifndef ANGLE_H
#define ANGLE_H

typedef struct angles angle_t;
struct angles
{
    double sina;
    double cosa;
};

angle_t angle_init(double sina, double cosa);

#endif // ANGLE_H
