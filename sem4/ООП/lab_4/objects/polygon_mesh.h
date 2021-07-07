#ifndef POLYGON_MESH_H
#define POLYGON_MESH_H

#include <memory>
#include "../exceptions/shape_build_exception.h"
#include "../math/matrix.h"
#include "../math/point.h"

namespace objects {

using math::Point;

class PolygonMesh {
public:
    void addPoint(Point &p);
    void addEdge(size_t first, size_t second);
    void transform(const std::shared_ptr<math::Matrix> matrix);
    std::vector<std::pair<Point, Point>> getLines();
private:
    std::vector<Point> _points;
    std::vector<std::pair<size_t, size_t>> _edges;
};

}

#endif
