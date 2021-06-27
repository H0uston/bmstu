#include "point.h"

Point3D::Point3D(double x, double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}

Point3D::Point3D(double x, double y, double z, double a)
{
    _x = x;
    _y = y;
    _z = z;
    _w = a;
}

Point3D::Point3D()
{

}

double Point3D::get_x()
{
    return _x;
}

double Point3D::get_y()
{
    return _y;
}

double Point3D::get_z()
{
    return _z;
}

double Point3D::get_w()
{
    return _w;
}

double Point3D::get_x() const
{
    return _x;
}

double Point3D::get_y() const
{
    return _y;
}

double Point3D::get_z() const
{
    return _z;
}

double Point3D::get_w() const
{
    return _w;
}

void Point3D::set_x(double x)
{
    _x = x;
}

void Point3D::set_y(double y)
{
    _y = y;
}

void Point3D::set_z(double z)
{
    _z = z;
}

void Point3D::set_w(double a)
{
    _w = a;
}

Point3D Point3D::operator + (Point3D p)
{
    Point3D point(this->get_x(), this->get_y(), this->get_z(), this->get_w());
    point._x += p.get_x();
    point._y += p.get_y();
    point._z += p.get_z();
    point._w += p.get_w();
    return point;
}

Point3D Point3D::operator + (const Point3D* p)
{
    Point3D point(this->get_x(), this->get_y(), this->get_z(), this->get_w());
    point._x += p->get_x();
    point._y += p->get_y();
    point._z += p->get_z();
    point._w += p->get_w();
    return point;
}

Point3D Point3D::operator - (Point3D p)
{
    Point3D point(this->get_x(), this->get_y(), this->get_z(), this->get_w());
    point._x -= p.get_x();
    point._y -= p.get_y();
    point._z -= p.get_z();
    point._w -= p.get_w();
    return point;
}

Point3D Point3D::operator - (const Point3D* p)
{
    Point3D point(this->get_x(), this->get_y(), this->get_z(), this->get_w());
    point._x -= p->get_x();
    point._y -= p->get_y();
    point._z -= p->get_z();
    point._w -= p->get_w();
    return point;
}

Point3D Point3D::operator = (Point3D p)
{
    this->_x = p.get_x();
    this->_y = p.get_y();
    this->_z = p.get_z();
    this->_w = p.get_w();
    return *this;
}

Point3D Point3D::operator * (const double c)
{
    Point3D point(this->get_x(), this->get_y(), this->get_z(), this->get_w());
    point._x *= c;
    point._y *= c;
    point._z *= c;
    point._w *= c;
    return point;
}

Point3D Point3D::operator % (const Point3D& p)
{
    return Point3D(_y * p.get_z() - _z * p.get_y(),
                   _z * p.get_x() - _x * p.get_z(),
                   _x * p.get_y() - _y * p.get_x());
}

double Point3D::operator ^ (const Point3D& p)
{
    return this->get_x() * p.get_x() + this->get_y() * p.get_y() + this->get_z() * p.get_z();
}

void Point3D::set(double x, double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}

void Point3D::set(double x, double y, double z, double w)
{
    _x = x;
    _y = y;
    _z = z;
    _w = w;
}

double Point3D::module() const
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}

void Point3D::normalize()
{
    double mod = module();
    _x /= mod;
    _y /= mod;
    _z /= mod;
}

double Point3D::operator [] (int index)
{
    if (index == 0)
        return _x;
    else if (index == 1)
        return _y;
    else if (index == 2)
        return _z;
    else if (index == 3)
    {
        return _w;
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Ошибка","Ошибка индексации!");
        messageBox.setFixedSize(500,200);
        exit(1);
    }

}

Point3D Point3D::operator * (Matrix m)
{
    if ((m.get_count_rows() == 4 && m.get_count_columns() == 4) ||
        (m.get_count_rows() == 3 && m.get_count_columns() == 3))
    {
        Point3D res;
        res.set_x(_x * m[0][0] + _y * m[1][0] + _z * m[2][0]);
        res.set_y(_x * m[0][1] + _y * m[1][1] + _z * m[2][1]);
        res.set_z(_x * m[0][2] + _y * m[1][2] + _z * m[2][2]);
        return res;
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Ошибка","Ошибка в размерах матриц!");
    messageBox.setFixedSize(500,200);
    exit(1);
}

Point3D Point3D::operator ^ (Matrix m)
{
    if (m.get_count_rows() == 4 && m.get_count_columns() == 4)
    {
        Point3D result;
        result.set_x(_x * m[0][0] + _y * m[1][0] + _z * m[2][0] + m[3][0]);
        result.set_y(_x * m[0][1] + _y * m[1][1] + _z * m[2][1] + m[3][1]);
        result.set_z(_x * m[0][2] + _y * m[1][2] + _z * m[2][2] + m[3][2]);
        return result;
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Ошибка","Ошибка в размерах матриц!");
    messageBox.setFixedSize(500,200);
    exit(1);
}

double Point3D::operator * (Point3D p)
{
    return _x * p.get_x() + _y * p.get_y() + _z * p.get_z();
}
