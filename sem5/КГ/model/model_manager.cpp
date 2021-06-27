#include "model_manager.h"

Model_manager::Model_manager()
{

}

void Model_manager::rotate_x(Model& model, const double angle)
{
    double rad = angle * M_PI / 180;
    Matrix rotate_x(4, 4);
    rotate_x.makeIdentity();
    rotate_x[1][1] = cos(rad);
    rotate_x[1][2] = sin(rad);
    rotate_x[2][1] = -rotate_x[1][2];
    rotate_x[2][2] = rotate_x[1][1];
    model.set_rotation(model.get_rotation() * rotate_x);
}

void Model_manager::rotate_y(Model& model, const double angle)
{
    double rad = angle * M_PI / 180;
    Matrix rotate_y(4, 4);
    rotate_y.makeIdentity();
    rotate_y[0][0] = cos(rad);
    rotate_y[0][2] = -sin(rad);
    rotate_y[2][0] = -rotate_y[2][0];
    rotate_y[2][2] = rotate_y[0][0];
    model.set_rotation(model.get_rotation() * rotate_y);
}

void Model_manager::rotate_z(Model& model, const double angle)
{
    double rad = angle * M_PI / 180;
    Matrix rotate_z(4, 4);
    rotate_z.makeIdentity();
    rotate_z[0][0] = cos(rad);
    rotate_z[0][1] = sin(rad);
    rotate_z[1][0] = -rotate_z[0][1];
    rotate_z[1][1] = rotate_z[0][0];
    model.set_rotation(model.get_rotation() * rotate_z);
}

void Model_manager::move(Model& model, Point3D parametr)
{
    model.set_translation(model.get_translation() + parametr);
}

void Model_manager::move(Train& model, Point3D parametr)
{
    model.set_translation(model.get_translation() + parametr);
}

Matrix Model_manager::get_model_view(Model &model)
{
    Matrix translation(4, 4);
    Point3D translate(model.get_translation());
    translation.makeIdentity();
    translation[3][0] = translate.get_x();
    translation[3][1] = translate.get_y();
    translation[3][2] = translate.get_z();
    return model.get_rotation() * translation * model.get_scale();
}

void Model_manager::scale(Model& model, const double koef)
{
    Matrix scale(4,4);
    scale[0][0] = koef;
    scale[1][1] = koef;
    scale[2][2] = koef;
    scale[3][3] = 1;
    model.set_scale(model.get_scale() * scale);
}
