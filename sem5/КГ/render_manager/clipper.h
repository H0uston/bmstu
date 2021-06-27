#ifndef CLIPPER_H
#define CLIPPER_H

#include "clipper_cube.h"
#include "../model/triangle.h"
#include <iostream>
#include <vector>

class Clipper
{
public:
    Clipper();
    int clip_polygon(Triangle& triangle);
private:
    void _correct_points(std::vector<Point3D>& points);
    int _polygon_clip_to_plane(const std::vector<Point3D> in_vertices, const Clipper_cube &boundary, std::vector<Point3D>& out_vertices);
};

#endif // CLIPPER_H
