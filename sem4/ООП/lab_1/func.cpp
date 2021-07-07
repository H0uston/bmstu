#include "func.h"

static void change_shape_rotate_x(shape_t &shape, angle_t angle)
{
    int n = get_count_of_points(shape);
    for (int i = 0; i < n; i++)
    {
        double y = get_y_index_point(shape, i) * angle.cosa - get_z_index_point(shape, i) * angle.sina;
        double z = get_y_index_point(shape, i) * angle.sina + get_z_index_point(shape, i) * angle.cosa;
        fill_y_index_point(shape, i, y);
        fill_z_index_point(shape, i, z);
    }
}

// Функция поворота модели вокруг оси X
int rotate_x(shape_t &shape, parameters_t &parameters)
{
    double angle = get_angle(parameters);
    if (fabs(angle) < EPS)
    {
        return WARNING;
    }
    double cosa = cos(angle * M_PI / TO_RAD_180);
    double sina = sin(angle * M_PI / TO_RAD_180);

    angle_t angles = angle_init(sina, cosa);

    change_shape_rotate_x(shape, angles);
    return OK;
}

static void change_shape_rotate_y(shape_t &shape, angle_t angle)
{
    int n = get_count_of_points(shape);
    for (int i = 0; i < n; i++)
    {
        double x = get_x_index_point(shape, i) * angle.cosa - get_z_index_point(shape, i) * angle.sina;
        double z = get_x_index_point(shape, i) * angle.sina + get_z_index_point(shape, i) * angle.cosa;
        fill_x_index_point(shape, i, x);
        fill_z_index_point(shape, i, z);
    }
}

// Функция поворота модели вокруг оси Y
int rotate_y(shape_t &shape, parameters_t &parameters)
{
    double angle = get_angle(parameters);
    if (fabs(angle) < EPS)
    {
        return WARNING;
    }
    double cosa = cos(angle * M_PI / TO_RAD_180);
    double sina = sin(angle * M_PI / TO_RAD_180);

    angle_t angles = angle_init(sina, cosa);

    change_shape_rotate_y(shape, angles);
    return OK;
}

static void change_shape_rotate_z(shape_t &shape, angle_t angle)
{
    int n = get_count_of_points(shape);
    for (int i = 0; i < n; i++)
    {
        double x = get_x_index_point(shape, i) * angle.cosa - get_y_index_point(shape, i) * angle.sina;
        double y = get_x_index_point(shape, i) * angle.sina + get_y_index_point(shape, i) * angle.cosa;
        fill_x_index_point(shape, i, x);
        fill_y_index_point(shape, i, y);
    }
}

// Функция поворота модели вокруг оси Z
int rotate_z(shape_t &shape, parameters_t &parameters)
{
    double angle = get_angle(parameters);
    if (fabs(angle) < EPS)
    {
        return WARNING;
    }
    double cosa = cos(angle * M_PI / TO_RAD_180);
    double sina = sin(angle * M_PI / TO_RAD_180);

    angle_t angles = angle_init(sina, cosa);

    change_shape_rotate_z(shape, angles);
    return OK;
}

// Функция перноса модели (по координатам)
int move(shape_t &shape, parameters_t &parameters)
{
    int count_of_points = get_count_of_points(shape);
    for (int i = 0; i < count_of_points; i++)
    {
        fill_x_index_point(shape, i, get_x_index_point(shape, i) + parameters.dx);
        fill_y_index_point(shape, i, get_y_index_point(shape, i) + parameters.dy);
        fill_z_index_point(shape, i, get_z_index_point(shape, i) + parameters.dz);
    }
    return OK;
}

// Функция масштабирования модели
int scale(shape_t &shape, parameters_t &parameters)
{
    int count_of_points = get_count_of_points(shape);
    for (int i = 0; i < count_of_points; i++)
    {
        fill_x_index_point(shape, i, get_x_index_point(shape, i) * parameters.kx);
        fill_y_index_point(shape, i, get_y_index_point(shape, i) * parameters.ky);
        fill_z_index_point(shape, i, get_z_index_point(shape, i) * parameters.kz);
    }
    return OK;
}

// Функция печати модели на сцену
int set_view(shape_t shape, QGraphicsScene &scene)
{
    int code_error = OK;
    draw_axis(scene);

    draw(shape, scene);

    return code_error;
}
