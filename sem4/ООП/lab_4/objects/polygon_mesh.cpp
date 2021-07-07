#include "polygon_mesh.h"

namespace objects {

void PolygonMesh::addPoint(math::Point &p)
{
    _points.push_back(p);
}

void PolygonMesh::addEdge(size_t first, size_t second) {
    if (first < 0 || second < 0 || first >= _points.size() || second >= _points.size())
    {
        throw exceptions::ShapeBuildException("Wrong point number");
    }
    _edges.emplace_back(first, second);
}

void PolygonMesh::transform(const std::shared_ptr<math::Matrix> matrix)
{
    for (auto &point: _points)
    {
        point.transform(matrix);
    }
}

std::vector<std::pair<math::Point, math::Point> > PolygonMesh::getLines()
{
    std::vector<std::pair<Point, Point>> lines;
    for (auto &edge: _edges)
    {
        lines.emplace_back(_points[edge.first], _points[edge.second]);
    }

    return lines;
}

}
