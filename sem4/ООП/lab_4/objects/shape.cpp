#include "shape.h"

namespace objects {

Shape::Shape(std::string name): Object(name), _mesh(new PolygonMesh) {}

void Shape::addPoint(math::Point &p)
{
    _mesh->addPoint(p);
}

void Shape::addEdge(size_t first, size_t second)
{
    _mesh->addEdge(first, second);
}

void Shape::transform(const std::shared_ptr<math::Matrix> matrix)
{
    _mesh->transform(matrix);
}

void Shape::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}


}
