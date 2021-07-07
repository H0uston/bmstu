#ifndef QT_DRAWER_H
#define QT_DRAWER_H

#include <QPainter>
#include <cmath>
#include "base_drawer.h"

namespace drawing {

class QtDrawer: public BaseDrawer {
public:
    explicit QtDrawer(QPainter *painter);
    void drawLine(const Point &p1, const Point &p2) override;
private:
    QPainter *_painter;
};

}

#endif
