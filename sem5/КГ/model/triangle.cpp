#include "triangle.h"

Triangle::Triangle()
{
    _points.resize(3);

}

void Triangle::set_points(Point3D& p1, Point3D& p2, Point3D& p3)
{
    _points.resize(3);
    _points = std::vector<Point3D> {p1, p2, p3};
}

Triangle::Triangle(Point3D& p1, Point3D& p2, Point3D& p3)
{
    _points.resize(3);
    set_points(p1, p2, p3);
}

std::vector<Point3D>& Triangle::get_points()
{
    return _points;
}

void Triangle::set_cull_flag()
{
    _cull_flag = true;
}

void Triangle::unset_cull_flag()
{
    _cull_flag = false;
}

bool Triangle::get_cull_flag()
{
    return _cull_flag;
}


void Triangle::set_normal_vector(Point3D& point)
{
    _normal_vector = point;
}

Point3D& Triangle::get_normal_vector()
{
    return _normal_vector;
}

bool Triangle::is_visiable(Point3D camera)
{
    return (this->get_normal_vector().get_x() * camera.get_x()) + (this->get_normal_vector().get_y() * camera.get_y() +
                                                                   this->get_normal_vector().get_z() * camera.get_z()) < EPS;
}
