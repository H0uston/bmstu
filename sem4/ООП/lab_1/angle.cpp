#include "angle.h"

angle_t angle_init(double sina, double cosa)
{
    angle_t angle;
    angle.sina = sina;
    angle.cosa = cosa;
    return angle;
}
