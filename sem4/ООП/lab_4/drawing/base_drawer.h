#ifndef BASE_DRAWER_H
#define BASE_DRAWER_H

#include "../math/point.h"

namespace drawing {

using math::Point;

class BaseDrawer {
public:
    virtual ~BaseDrawer() = default;
    virtual void drawLine(const Point &p1, const Point &p2) = 0;
};

}

#endif
