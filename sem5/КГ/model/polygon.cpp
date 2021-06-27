#include "polygon.h"

Polygon::Polygon()
{
    _name = "";
}

bool Polygon::is_ready()
{
    return _name != "" && _triangles.size() > 0;
}

void Polygon::set_name(std::string& name)
{
    _name = name;
}

void Polygon::append_triangle(Triangle &triangle)
{
    _triangles.push_back(triangle);
}

void Polygon::append_triangle(Point3D& p1, Point3D& p2, Point3D& p3)
{
    Triangle triangle(p1, p2, p3);
    _triangles.push_back(triangle);
}

std::vector<Triangle>& Polygon::get_triangles()
{
    return _triangles;
}

std::vector<Triangle> Polygon::get_triangles() const
{
    return _triangles;
}

size_t Polygon::get_count_of_triangles()
{
    return _triangles.size();
}

size_t Polygon::get_count_of_triangles() const
{
    return _triangles.size();
}


std::string Polygon::get_name() const
{
    return _name;
}

void Polygon::set_color(QColor color)
{
    _color = color;
}

QColor Polygon::get_color()
{
    return _color;
}

QColor Polygon::get_color() const
{
    return _color;
}

void Polygon::find_center()
{
    double max_x, max_y, max_z, min_x, min_y, min_z;
    std::vector<Triangle> triangles = _triangles;
    size_t trg_count = triangles.size();
    for (size_t j = 0; j < trg_count; j++)
    {
        std::vector<Point3D> points = triangles[j].get_points();
        size_t pnt_count = points.size();
        for (size_t k = 0; k < pnt_count; k++)
        {
            if (j == 0 && k == 0)
            {
                max_x = points[k].get_x();
                max_y = points[k].get_y();
                max_z = points[k].get_z();
                min_x = points[k + 1].get_x();
                min_y = points[k + 1].get_y();
                min_z = points[k + 1].get_z();
            }

            if (points[k].get_x() > max_x)
                max_x = points[k].get_x();
            else if (points[k].get_x() < min_x)
                min_x = points[k].get_x();

            if (points[k].get_y() > max_y)
                max_y = points[k].get_y();
            else if (points[k].get_y() < min_y)
                min_y = points[k].get_y();

            if (points[k].get_z() > max_z)
                max_z = points[k].get_z();
            else if (points[k].get_z() < min_z)
                min_z = points[k].get_z();
        }
    }
    center.set(min_x + (max_x - min_x) / 2.0,
               min_y + (max_y - min_y) / 2.0,
               min_z + (max_z - min_z) / 2.0);
}

Point3D& Polygon::get_center()
{
    return center;
}

void Polygon::change_center(Point3D p)
{
    center = center + p;
}
