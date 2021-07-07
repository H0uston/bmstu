#ifndef SHAPE_BUILDER_H
#define SHAPE_BUILDER_H

#include "memory"
#include "../objects/shape.h"

namespace uploading {

using objects::Shape;

class ShapeBuilder {
public:
    ShapeBuilder() = default;

    void reset(std::string name);
    void addPoint(math::Point &point);
    void addEdge(size_t first, size_t second);
    std::shared_ptr<Shape> getResult();

private:
    std::shared_ptr<Shape> _shape;
};

}

#endif
