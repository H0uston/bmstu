#include "clipper.h"
#include <QDebug>

Clipper::Clipper()
{

}

int Clipper::_polygon_clip_to_plane(const std::vector<Point3D> in_vertices, const Clipper_cube &boundary, std::vector<Point3D>& out_vertices)
{
    if (in_vertices.size() <= 2 ) {
        qDebug() << "Bad polygon given to clip";
        exit(1);
    }

    Point3D intersect_p;
    double t;
    size_t pt1, pt2, j;
    int found;
    bool flag_next_inside = false;
    size_t max_out_len = in_vertices.size() * 2;
    pt1 = (in_vertices.size() - 1);

    for ( j = 0; j < in_vertices.size(); j++ )
    {
        pt2 = j;
        if (boundary.point_is_inside(in_vertices[pt2]))    //  Случай 1 & 4
            if ( boundary.point_is_inside(in_vertices[pt1])) //  Случай 1: Оба внутри
            {
                if (out_vertices.size() >= max_out_len)
                {
                    qDebug() << "Clip buffer too small";
                    out_vertices.clear();
                    return -1;
                }
                out_vertices.push_back(in_vertices[pt2]);
                flag_next_inside = true;
            }
            else  // Case 4: первый снаружи, второй внутри
            {
                boundary.line_intersect( in_vertices[pt1], in_vertices[pt2], &found, intersect_p, t);
                if (!found)
                {
                    qDebug() << "Failed to find intersection point";
                    out_vertices.clear();
                    return -1;
                }

                if (out_vertices.size() >= max_out_len - 1)
                {
                    qDebug() << "Clip buffer too small";
                    out_vertices.clear();
                    return -1;
                }
                out_vertices.push_back(intersect_p);
                out_vertices.push_back(in_vertices[pt2]);
            }
        else
        {                                        //  Случай 2 & 3 (3 - оба снаружи)
            if ( boundary.point_is_inside(in_vertices[pt1])) // второй снаружи, первый внутри
            {
                boundary.line_intersect(in_vertices[pt1], in_vertices[pt2], &found, intersect_p, t);
                if (!found)
                {
                    qDebug() << "Failed to find intersection point (shouldn't happen)";
                    out_vertices.clear();
                    return -1;
                }
                if (out_vertices.size() >= max_out_len)
                {
                    qDebug() << "Clip buffer too small";
                    out_vertices.clear();
                    return -1;
                }
                out_vertices.push_back(intersect_p);
            }
        }
        pt1 = pt2;
    }
    return 0;
}

void Clipper::_correct_points(std::vector<Point3D>& points)
{
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        if (fabs(points[i].get_x() - points[i + 1].get_x()) < EPS &&
            fabs(points[i].get_y() - points[i + 1].get_y()) < EPS &&
            fabs(points[i].get_z() - points[i + 1].get_z()) < EPS)
        {
            points.erase(points.begin() + (i + 1));
            i--;
        }
    }
}

int Clipper::clip_polygon(Triangle& triangle)
{
    std::vector<Point3D>& in_points = triangle.get_points();
    std::vector<Point3D> out_points;
    Clipper_cube boundary_list[] = {
        Clipper_cube( -1, 0, 0, 1 ),   // X =  1 (-x+w=0; X< 1 внутри)
        Clipper_cube(  1, 0, 0, 1 ),   // X = -1 ( x+w=0; X>-1 внутри)
        Clipper_cube(  0,-1, 0, 1 ),   // Y =  1 (-y+w=0; Y< 1 внутри)
        Clipper_cube(  0, 1, 0, 1 ),   // Y = -1 ( y+w=0; Y>-1 внутри)
        Clipper_cube(  0, 0,-1, 1 ),   // Z =  1 (-z+w=0; Z< 1 внутри)
        Clipper_cube(  0, 0, 1, 1 )    // Z = -1 ( z+w=0; Z>-1 внутри)
    };
    std::vector<Point3D> start = in_points;
    // Отсечение по всем сторонам отсекателя
    for (int b = 0; b < 6; b++)
    {
        int status = _polygon_clip_to_plane(in_points, boundary_list[b], out_points);
        if (status != 0)
            return 0;
        in_points = out_points;

        //  Если многоугольник пуст
        if (out_points.size() == 0 )
            break;
        out_points.clear();
    }
    if (in_points.size() > 3)
        _correct_points(in_points);
    return in_points.size();
}
