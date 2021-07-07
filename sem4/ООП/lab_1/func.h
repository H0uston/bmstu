#ifndef FUNC_H
#define FUNC_H

#include <math.h>
#include <QGraphicsScene>

#include "shape.h"
#include "config.h"
#include "angle.h"
#include "draw.h"

#define TO_RAD_180 180
#define EPS 0.00001

int rotate_x(shape_t &shape, parameters_t &parameters);
int rotate_y(shape_t &shape, parameters_t &parameters);
int rotate_z(shape_t &shape, parameters_t &parameters);
int move(shape_t &shape, parameters_t &parameters);
int scale(shape_t &shape, parameters_t &parameters);
int set_view(shape_t shape, QGraphicsScene &scene);

#endif // FUNC_H
