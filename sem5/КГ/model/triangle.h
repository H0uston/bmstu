#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include <vector>
#include "config.h"

class Triangle
{
public:
    Triangle();
    Triangle(Point3D& p1, Point3D& p2, Point3D& p3);
    void set_points(Point3D& p1, Point3D& p2, Point3D& p3);

    std::vector<Point3D>& get_points();

    void set_cull_flag();
    void unset_cull_flag();
    bool get_cull_flag();

    void set_normal_vector(Point3D&);
    Point3D& get_normal_vector();

    bool is_visiable(Point3D camera);
private:
    std::vector<Point3D> _points;
    bool _cull_flag = false;
    Point3D _normal_vector;
};

#endif // TRIANGLE_H
