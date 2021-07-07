#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QGraphicsScene>
#include "config.h"
#include "shape.h"
#include "input_shape.h"
#include "output.h"
#include "func.h"

enum {LOAD, SAVE, ROTATE_X, ROTATE_Y, ROTATE_Z, SCALE, MOVE, DRAW, FREE_MEMORY};
int controller(QGraphicsScene &scene, parameters_t parameters, int action);

#endif // CONTROLLER_H
