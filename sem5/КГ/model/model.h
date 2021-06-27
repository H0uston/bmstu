#ifndef MODEL_H
#define MODEL_H

#include "polygon.h"
#include "../math/matrix.h"

class Model
{
public:
    Model();

    void append_polygon(Polygon&);
    std::vector<Polygon>& get_polygons();
    size_t get_count_of_polygons();

    Matrix& get_scale();
    void set_scale(Matrix mtr);

    Matrix& get_rotation();
    void set_rotation(Matrix rotation);
    Point3D get_translation();
    void set_translation(Point3D translation);

    Point3D get_center();
    bool is_center_found();
    void set_center(Point3D center);
    void find_center();

private:
    Point3D _center_point = Point3D(0,0,0);
    bool _center_is_found = false;

    std::vector<Polygon> _polygons;
    Matrix _scale = Matrix(4,4);
    Matrix _rotation = Matrix(4,4);
    Point3D _translation = Point3D(0,0,0);
};

#endif // MODEL_H
