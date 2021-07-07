#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

#include "config.h"
#include "shape.h"

typedef struct center center_t;
struct center
{
    double x;
    double y;
};

center_t center_init(void);
void draw_axis(QGraphicsScene &scene);
int draw(shape_t shape, QGraphicsScene &scene);

#endif // DRAW_H
