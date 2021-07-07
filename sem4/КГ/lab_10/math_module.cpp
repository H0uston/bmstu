#include "math_module.h"
void rotate_point_x(point_3d &point, double angle)
{
    if (fabs(angle) >= EPS)
    {
        double tmp_x = point.x, tmp_y = point.y, tmp_z = point.z;
        point.x = tmp_x;
        point.y = tmp_y * cos(angle) - tmp_z * sin(angle);
        point.z = tmp_y * sin(angle) + tmp_z * cos(angle);
    }
}

void rotate_point_y(point_3d &point, double angle)
{
    if (fabs(angle) >= EPS)
    {
        double tmp_x = point.x, tmp_y = point.y, tmp_z = point.z;
        point.x = tmp_x * cos(angle) - tmp_z * sin(angle);
        point.y = tmp_y;
        point.z = tmp_x * sin(angle) + tmp_z * cos(angle);
    }
}

void rotate_point_z(point_3d &point, double angle)
{
    if (fabs(angle) >= EPS)
    {
        double tmp_x = point.x, tmp_y = point.y, tmp_z = point.z;
        point.x = tmp_x * cos(angle) - tmp_y * sin(angle);
        point.y = tmp_x * sin(angle) + tmp_y * cos(angle);
        point.z = tmp_z;
    }
}

void rotate_point(point_3d &point, transform_params &params)
{
    double k = (double)M_PI / 180;
    rotate_point_x(point, params.angle_x * k);
    rotate_point_y(point, params.angle_y * k);
    rotate_point_z(point, params.angle_z * k);
}
