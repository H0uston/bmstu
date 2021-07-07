#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "object.h"
#include "polygon_mesh.h"
#include "../math/point.h"

namespace objects {

using math::Point;

class Shape: public Object {
public:
    Shape(std::string);

    void addPoint(Point &p);
    void addEdge(size_t first, size_t second);
    void transform(const std::shared_ptr<Matrix> matrix) override;
    void accept(std::shared_ptr<Visitor> visitor) override;
    std::shared_ptr<PolygonMesh> getMesh() { return _mesh; }

private:
    std::shared_ptr<PolygonMesh> _mesh;
};

}

#endif
