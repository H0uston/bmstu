#include "train.h"
#include <string.h>
#include <QtDebug>

Train::Train(Model& model)
{
    _rotation_wheel.makeIdentity();
    std::vector<Polygon> polygons = model.get_polygons();
    size_t count = polygons.size(), pos;
    std::string str;
    for (size_t i = 0; i < count; i++)
    {
        str = polygons[i].get_name();
        if ((pos = str.find("Corpus")) != std::string::npos)
        {
            polygons[i].set_color(Qt::white);
        }
        else if ((pos = str.find("wheel")) != std::string::npos)
        {
            polygons[i].set_color(Qt::black);
            polygons[i].find_center();
            _wheels_indexes.push_back(i);
        }
        else if ((pos = str.find("glass")) != std::string::npos)
        {
            polygons[i].set_color(Qt::blue);
        }
        else if ((pos = str.find("mark")) != std::string::npos)
        {
            polygons[i].set_color(Qt::red);
        }
        else if ((pos = str.find("light")) != std::string::npos)
        {
            polygons[i].set_color(Qt::yellow);
        }
        this->append_polygon(polygons[i]);
    }
    this->set_translation(model.get_translation());
    this->set_rotation(model.get_rotation());
    rotate_wheels();
    find_center();
}


Train::Train()
{
    _rotation_wheel.makeIdentity();
}

std::vector<int> Train::get_wheels_indexes()
{
    return _wheels_indexes;
}

Matrix Train::get_rotation_wheel()
{
    return _rotation_wheel;
}

void Train::rotate_wheels()
{
    double rad = angle * M_PI / 180;
    _rotate_matrix.makeIdentity();
    _rotate_matrix[0][0] = cos(rad);
    _rotate_matrix[0][2] = -sin(rad);
    _rotate_matrix[2][0] = -_rotate_matrix[0][2];
    _rotate_matrix[2][2] = _rotate_matrix[0][0];
    _rotation_wheel = _rotation_wheel * _rotate_matrix;
}

Matrix Train::get_wheel_view(Point3D& center)
{
    Matrix translation(4, 4), new_center(4, 4), old_center(4, 4);
    Point3D translate(get_translation());
    translation.makeIdentity();
    new_center.makeIdentity();
    old_center.makeIdentity();
    translation[3][0] = translate.get_x();
    translation[3][1] = translate.get_y();
    translation[3][2] = translate.get_z();
    old_center[3][0] = center.get_x();
    old_center[3][1] = center.get_y();
    old_center[3][2] = center.get_z();
    new_center[3][0] = -old_center[3][0];
    new_center[3][1] = -old_center[3][1];
    new_center[3][2] = -old_center[3][2];
    Matrix result = (new_center * _rotation_wheel * old_center) * get_rotation() * translation * get_scale();
    return result;
}
