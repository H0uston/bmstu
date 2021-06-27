#ifndef GROUND_H
#define GROUND_H

#include <QColor>
#include "model.h"

class Ground : public Model
{
public:
    Ground(double x, double y, double z);

private:
    QColor color = GRASS;
};

#endif // GROUND_H
