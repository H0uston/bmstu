#include "shape_builder.h"

namespace uploading {

void ShapeBuilder::reset(std::string name)
{
    _shape.reset();
    _shape = std::shared_ptr<Shape>(new Shape(name));
}

void ShapeBuilder::addPoint(math::Point &point)
{
    _shape->addPoint(point);
}

void ShapeBuilder::addEdge(size_t first, size_t second)
{
    _shape->addEdge(first, second);
}

std::shared_ptr<objects::Shape> ShapeBuilder::getResult()
{
    return _shape;
}

}
