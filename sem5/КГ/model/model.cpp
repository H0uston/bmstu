#include "model.h"

Model::Model()
{
    _rotation.makeIdentity();
    _scale.makeIdentity();
}

void Model::append_polygon(Polygon &polygon)
{
    _polygons.push_back(polygon);
}

std::vector<Polygon>& Model::get_polygons()
{
    return _polygons;
}

size_t Model::get_count_of_polygons()
{
    return _polygons.size();
}

Matrix& Model::get_scale()
{
    return _scale;
}
void Model::set_scale(Matrix mtr)
{
    _scale = mtr;
}

Matrix& Model::get_rotation()
{
    return _rotation;
}

Point3D Model::get_translation()
{
    return _translation;
}

void Model::set_rotation(Matrix rotation)
{
    _rotation = rotation;
}

void Model::set_translation(Point3D translation)
{
    _translation = translation;
}

void Model::find_center()
{
    double max_x = 0, min_x = 0, max_y = 0, min_y = 0, max_z = 0, min_z = 0;
    size_t pol_count = get_count_of_polygons();
    for (size_t i = 0; i < pol_count; i++)
    {
        std::vector<Triangle> triangles = _polygons[i].get_triangles();
        size_t trg_count = _polygons[i].get_count_of_triangles();
        for (size_t j = 0; j < trg_count; j++)
        {
            std::vector<Point3D> points = triangles[j].get_points();
            size_t pnt_count = points.size();
            for (size_t k = 0; k < pnt_count; k++)
            {
                if (i == 0 && j == 0 && k == 0)
                {
                    max_x = points[k].get_x();
                    max_y = points[k].get_y();
                    max_z = points[k].get_z();
                    min_x = points[k + 1].get_x();
                    min_y = points[k + 1].get_y();
                    min_z = points[k + 1].get_z();
                }

                if (points[k].get_x() > max_x)
                    max_x = points[k].get_x();
                else if (points[k].get_x() < min_x)
                    min_x = points[k].get_x();

                if (points[k].get_y() > max_y)
                    max_y = points[k].get_y();
                else if (points[k].get_y() < min_y)
                    min_y = points[k].get_y();

                if (points[k].get_z() > max_z)
                    max_z = points[k].get_z();
                else if (points[k].get_z() < min_z)
                    min_z = points[k].get_z();
            }
        }
    }

    _center_point.set(min_x + (max_x - min_x) / 2.0,
               min_y + (max_y - min_y) / 2.0,
               min_z + (max_z - min_z) / 2.0);
    _center_is_found = true;
}

bool Model::is_center_found()
{
    return _center_is_found;
}

Point3D Model::get_center()
{
    return _center_point;
}
