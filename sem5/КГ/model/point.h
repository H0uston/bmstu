#ifndef POINT_H
#define POINT_H

#include <cmath>
#include "../math/matrix.h"

class Point3D
{
public:
    Point3D();
    Point3D(double x, double y, double z);
    Point3D(double x, double y, double z, double w);

    double get_x();
    double get_y();
    double get_z();
    double get_w();
    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_w() const;

    void set_x(double x);
    void set_y(double y);
    void set_z(double z);
    void set_w(double w);

    double operator [] (int index);
    Point3D operator +(const Point3D p);
    Point3D operator +(const Point3D* p);
    Point3D operator -(const Point3D p);
    Point3D operator -(const Point3D* p);
    Point3D operator =(const Point3D p);
    Point3D operator *(const double p);
    Point3D operator *(Matrix m);
    double operator * (Point3D p);
    Point3D operator %(const Point3D& p);
    double operator ^ (const Point3D& p);
    Point3D operator ^ (Matrix m);

    void set(double x, double y, double z);
    void set(double x, double y, double z, double w);

    double module() const;
    void normalize();

private:
    double _x;
    double _y;
    double _z;
    double _w = 1;
};

#endif // POINT_H
