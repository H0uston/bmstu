#include "clipper_cube.h"

double Clipper_cube::dot_prod(Point3D a, Point3D b) const
{
    return a.get_x()*b.get_x() + a.get_y()*b.get_y() + a.get_z()*b.get_z() + a.get_w()*b.get_w();
}

bool Clipper_cube::point_is_inside(Point3D p) const
{
  return A * p.get_x() + B * p.get_y() + C * p.get_z() + D * p.get_w() > 0;
}

void Clipper_cube::line_intersect(Point3D p1, Point3D p2, int *found, Point3D& intersect_p, double &t_val ) const
{
  Point3D P(A, B, C, D);
  double t = dot_prod(P, p2) - dot_prod(P, p1);

  if (fabs(t) < EPS)
    *found = 0;
  else
  {
    Point3D v1, v2;

    t_val = -dot_prod(P, p1) / t;

    v1 = p2 - p1;
    v2 = v1 * t_val;
    intersect_p = v2 + p1;
    *found = 1;
  }
}
