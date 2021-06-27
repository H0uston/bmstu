#include "scene.h"

static std::vector<Triangle> _triangulation(std::vector<Point3D>& points, Point3D normal)
{
    std::vector<Triangle> triangles;
    for (size_t i = 0; i < points.size() - 2; i++)
    {
        Triangle tr(points[0], points[i + 1], points[i + 2]);
        Point3D vector = normal;
        tr.set_normal_vector(vector);
        triangles.push_back(tr);
    }
    return triangles;
}

Railroad::Railroad(double x_start, double x_end, double y, double z)
{
    make_tunnel(x_start, 0, 0);
    double step = mound_length;
    for (double x = x_start; x <= x_end; x += step)
    {
        make_mound(x, y, z);
    }
    make_tunnel(x_end, 0, 0);
}

static void find_normal(Triangle& triangle)
{
    std::vector<Point3D> points = triangle.get_points();
    Point3D v1, v2;
    v1 = points[0] - points[1];
    v2 = points[2] - points[1];
    Point3D res = v2 % v1;
    res.normalize();
    triangle.set_normal_vector(res);
}

void Railroad::make_rails(double x, double y, double z, double length, double width, double height)
{
    const double halfl = length/2;
    const double halfw = width/2;
    const double halfh = height/2;
    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x - halfl, y - halfw, z);
        p2.set(x - halfl, y - halfw, z);
        p3.set(x - halfl, y - halfw, z + height);
        p4.set(x - halfl, y - halfw, z + height);
        tr1.set_points(p1, p2, p3);
        find_normal(tr1);
        tr2.set_points(p3, p4, p1);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "rail";
        polygon.set_name(name);
        polygon.set_color(_color_steel);
        this->append_polygon(polygon);
    }

    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x + halfl, y + halfw, z);
        p2.set(x - halfl, y + halfw, z);
        p3.set(x - halfl, y + halfw, z + height);
        p4.set(x + halfl, y + halfw, z + height);
        tr1.set_points(p1, p2, p3);
        find_normal(tr1);
        tr2.set_points(p3, p4, p1);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "rail";
        polygon.set_name(name);
        polygon.set_color(_color_steel);
        this->append_polygon(polygon);
    }

    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x - halfl, y - halfw, z + height);
        p2.set(x + halfl, y - halfw, z + height);
        p3.set(x + halfl, y + halfw, z + height);
        p4.set(x - halfl, y + halfw, z + height);
        tr1.set_points(p1, p2, p3);
        find_normal(tr1);
        tr2.set_points(p3, p4, p1);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "rail";
        polygon.set_name(name);
        polygon.set_color(_color_steel);
        this->append_polygon(polygon);
    }
}

void Railroad::make_wood_board(double x, double y, double z, double length, double width, double height)
{
    const double wood_halfl = length/2;
    const double wood_halfw = width/2;
    const double wood_halfh = height/2;
    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x - wood_halfl, y + wood_halfw, z + wood_halfh);
        p2.set(x + wood_halfl, y + wood_halfw, z + wood_halfh);
        p3.set(x + wood_halfl, y - wood_halfw, z + wood_halfh);
        p4.set(x - wood_halfl, y - wood_halfw, z + wood_halfh);
        tr1.set_points(p2, p1, p3);
        find_normal(tr1);
        tr2.set_points(p4, p3, p1);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "wood";
        polygon.set_name(name);
        polygon.set_color(_color_wood);
        this->append_polygon(polygon);
    }
}

void Railroad::make_mound(double x, double y, double z)
{
    const double halfl = mound_length/2;
    const double halfw = mound_width/2;
    const double halfh = mound_height/2;
    // Make mound 1
    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x - halfl, y - halfw, z);
        p2.set(x + halfl, y - halfw, z);
        p3.set(x + halfl, y - halfw + 1, z + halfh);
        p4.set(x - halfl, y - halfw + 1, z + halfh);
        tr1.set_points(p1, p2, p3);
        find_normal(tr1);
        tr2.set_points(p3, p4, p1);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "mound";
        polygon.set_name(name);
        polygon.set_color(_color_mound);
        this->append_polygon(polygon);
    }

    // Make mound 2
    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x - halfl, y - halfw + 3, z + mound_height);
        p2.set(x + halfl, y - halfw + 3, z + mound_height);
        p3.set(x + halfl, y - halfw + 1, z + halfh);
        p4.set(x - halfl, y - halfw + 1, z + halfh);


        tr1.set_points(p2, p1, p3);
        find_normal(tr1);
        tr2.set_points(p3, p1, p4);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "mound";
        polygon.set_name(name);
        polygon.set_color(_color_mound);
        this->append_polygon(polygon);
    }

    // Make mound 3
    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x - halfl, y + halfw - 3, z + mound_height);
        p2.set(x + halfl, y + halfw - 3, z + mound_height);
        p3.set(x + halfl, y - halfw + 3, z + mound_height);
        p4.set(x - halfl, y - halfw + 3, z + mound_height);

        tr1.set_points(p2, p1, p3);
        find_normal(tr1);
        tr2.set_points(p4, p3, p1);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "mound";
        polygon.set_name(name);
        polygon.set_color(_color_mound);
        this->append_polygon(polygon);
    }

    // Make mound 4
    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x - halfl, y + halfw - 3, z + mound_height);
        p2.set(x + halfl, y + halfw - 3, z + mound_height);
        p3.set(x + halfl, y + halfw - 1, z + halfh);
        p4.set(x - halfl, y + halfw - 1, z + halfh);
        tr1.set_points(p1, p2, p3);
        find_normal(tr1);
        tr2.set_points(p3, p4, p1);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "mound";
        polygon.set_name(name);
        polygon.set_color(_color_mound);
        this->append_polygon(polygon);
    }

    // Make mound 5
    {
        Polygon polygon;
        Point3D p1, p2, p3, p4;
        Triangle tr1, tr2;

        p1.set(x - halfl, y + halfw - 1, z + halfh);
        p2.set(x + halfl, y + halfw - 1, z + halfh);
        p3.set(x + halfl, y + halfw, z);
        p4.set(x - halfl, y + halfw, z);
        tr1.set_points(p1, p2, p3);
        find_normal(tr1);
        tr2.set_points(p3, p4, p1);
        find_normal(tr2);

        polygon.append_triangle(tr1);
        polygon.append_triangle(tr2);
        std::string name = "mound";
        polygon.set_name(name);
        polygon.set_color(_color_mound);
        this->append_polygon(polygon);
    }

    double start = x - halfl - 1;
        for (int i = 0; i < 5; i++)
        {
            make_wood_board(start, y, z + mound_height);
            start += 4;
        }

    double pos1 = y - 1.4, pos2 = y + 1.25;
    make_rails(x, pos1, z + mound_height + 0.5);
    make_rails(x, pos2, z + mound_height + 0.5);
}

void Railroad::make_tunnel(double x, double y, double z, double width, double height)
{
    Polygon polygon;
    Point3D p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12;
    std::vector<Triangle> triangles;
    std::vector<Point3D> points;

    double halfw = width / 2.0;
    double halfh = height / 2.0;

    p1.set(x, y - halfw, z);
    p2.set(x, y - halfw, z + halfh);
    p3.set(x, y - halfw + 1, z + halfh + 3);
    p4.set(x, y - halfw + 2, z + halfh + 6);
    p5.set(x, y - halfw + 5, z + halfh + 8);
    p6.set(x, y - 1, z + height);
    p7.set(x, y, z + height);
    p8.set(x, y + 1, z + height);
    p9.set(x, y + halfw - 5, z + halfh + 8);
    p10.set(x, y + halfw - 2, z + halfh + 6);
    p11.set(x, y + halfw - 1, z + halfh);
    p12.set(x, y + halfw, z);
    points = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12};
    Point3D normal(0,0,-1);
    triangles = _triangulation(points, normal);
    size_t count = triangles.size();
    for (size_t i = 0; i < count; i++)
        polygon.append_triangle(triangles[i]);
    std::string name = "tunnel";
    polygon.set_name(name);
    polygon.set_color(_color_tunel);
    this->append_polygon(polygon);
}
