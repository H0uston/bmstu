#include "shape.h"

// Функция обертка для получения кол-ва точек
int get_count_of_points(shape_t shape)
{
    return shape.count_of_points;
}

// Функция обертка для получения кол-ва ребер
int get_count_of_edges(shape_t shape)
{
    return shape.count_of_edges;
}

// Функция обертка для получения угла поворота
double get_angle(parameters_t parameters)
{
    return parameters.angle;
}

// Функция обертка для получения координаты по индексу
double get_x_index_point(shape_t &shape, int i)
{
    return shape.points[i].x;
}

// Функция обертка для получения координаты по индексу
double get_y_index_point(shape_t &shape, int i)
{
    return shape.points[i].y;
}

// Функция обертка для получения координаты по индексу
double get_z_index_point(shape_t &shape, int i)
{
    return shape.points[i].z;
}

// Функция обертка для заполнения координаты в модель
void fill_x_index_point(shape_t &shape, int i, double x)
{
    shape.points[i].x = x;
}

// Функция обертка для заполнения координаты в модель
void fill_y_index_point(shape_t &shape, int i, double y)
{
    shape.points[i].y = y;
}

// Функция обертка для заполнения координаты в модель
void fill_z_index_point(shape_t &shape, int i, double z)
{
    shape.points[i].z = z;
}

// Функция обертка для получения первого индекса связи
int get_first_index_edge(shape_t &shape, int i)
{
    return shape.edges[i].first;
}

// Функция обертка для получения второго индекса связи
int get_second_index_edge(shape_t &shape, int i)
{
    return shape.edges[i].second;
}

// Функция обертка для получения координаты точки
double get_x_coord_point(point_t &point)
{
    return point.x;
}

// Функция обертка для получения координаты точки
double get_y_coord_point(point_t &point)
{
    return point.y;
}

// Функция обертка для получения координаты точки
double get_z_coord_point(point_t &point)
{
    return point.z;
}

shape_t init()
{
    shape_t shape;
    shape.edges = nullptr;
    shape.points = nullptr;
    shape.count_of_edges = 0;
    shape.count_of_points = 0;
    return  shape;
}

int free_memory(shape_t &shape)
{
    int code_error = OK;
    free_shape(shape);
    return code_error;
}

// Функция очистки модели
void free_shape(shape_t shape)
{
    if (shape.edges != nullptr)
    {
        free(shape.edges);
    }
    if (shape.points != nullptr)
    {
        free(shape.points);
    }
}

// Функция создания модели
int allocate_shape(shape_t &shape)
{
    shape.points = static_cast<point_t*>(malloc(static_cast<unsigned long>(shape.count_of_points) * sizeof(point_t)));
    shape.edges = static_cast<edge_t*>(malloc(static_cast<unsigned long>(shape.count_of_edges) * sizeof(edge_t)));
    if (shape.points == nullptr || shape.edges == nullptr)
    {
        return ERR_MEMORY;
    }

    return OK;
}

