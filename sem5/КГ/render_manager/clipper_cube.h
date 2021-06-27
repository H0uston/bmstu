#ifndef CLIPPER_CUBE_H
#define CLIPPER_CUBE_H

#include "../model/point.h"
#include "config.h"

class Clipper_cube
{
    double A,B,C,D;                         // A*x + B*y + C*z + D*w = 0

public:
    Clipper_cube(double _A, double _B, double _C, double _D ) : A(_A), B(_B), C(_C), D(_D) {}

    double dot_prod(Point3D a, Point3D b) const;
    bool point_is_inside(Point3D p) const;
    void line_intersect(Point3D p1, Point3D p2, int *found, Point3D& intersect_p, double &t_val ) const;
};

#endif // CLIPPER_CUBE_H
