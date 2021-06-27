#include "ground.h"

#define POINTS 4

Ground::Ground(double x, double y, double z)
{
    Polygon polygon;
    Point3D p1, p2, p3, p4;
    p1.set(x, y, z);
    p2.set(-x, y, z);
    p3.set(-x, -y, z);
    p4.set(x, -y, z);
    Point3D normal(0, 0, 1);
    Triangle triangle1(p1, p2, p3);
    triangle1.set_normal_vector(normal);

    Triangle triangle2(p1, p4, p3);
    triangle2.set_normal_vector(normal);
    polygon.append_triangle(triangle1);
    polygon.append_triangle(triangle2);
    std::string name = "ground";
    polygon.set_name(name);
    polygon.set_color(color);
    this->append_polygon(polygon);
}
