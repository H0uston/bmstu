#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "model.h"

class Train : public Model
{
public:
    Train(Model& model);
    Train();
    std::vector<int> get_wheels_indexes();
    Matrix get_rotation_wheel();
    void rotate_wheels();
    Matrix get_wheel_view(Point3D& center);

private:
    Point3D _find_center_of_wheel(Polygon _wheel);
    std::vector<int> _wheels_indexes;
    Matrix _rotation_wheel = Matrix(4,4);
    Matrix _rotate_matrix = Matrix(4, 4);
    double angle = 15;
};

#endif // LOCOMOTIVE_H
