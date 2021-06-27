#ifndef POLYGON_H
#define POLYGON_H

#include "triangle.h"
#include <vector>
#include <string>
#include <QColor>

class Polygon
{
public:
    Polygon();
    bool is_ready();
    void set_name(std::string&);
    void append_triangle(Triangle& triangle);
    void append_triangle(Point3D& p1, Point3D& p2, Point3D& p3);

    void set_color(QColor color);
    QColor get_color();
    QColor get_color() const;

    std::vector<Triangle>& get_triangles();
    std::vector<Triangle> get_triangles() const;
    size_t get_count_of_triangles();
    size_t get_count_of_triangles() const;

    std::string get_name() const;
    void find_center();
    Point3D& get_center();
    void change_center(Point3D p);

private:
    std::string _name;
    std::vector<Triangle> _triangles;
    QColor _color;
    Point3D center;
};

#endif // POLYGON_H
