#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

class Vector3D : public Point3D
{
public:
    Vector3D();

    double module() const;
    void normalize();
};

#endif // VECTOR_H
