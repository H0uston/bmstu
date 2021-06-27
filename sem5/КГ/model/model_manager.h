#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "../math/matrix.h"
#include "train.h"

class Model_manager
{
public:
    Model_manager();

    void rotate_x(Model& model, const double angle);
    void rotate_y(Model& model, const double angle);
    void rotate_z(Model& model, const double angle);

    void move(Model& model, Point3D parametr);
    void move(Train& model, Point3D parametr);

    void scale(Model& model, const double angle);

    Matrix get_model_view(Model& model);
};

#endif // MODEL_MANAGER_H
