#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

#include "config.h"

typedef struct POINT_3D point_t;
struct POINT_3D
{
    double x;
    double y;
    double z;
};

typedef struct EDGE edge_t;
struct EDGE
{
    int first;
    int second;
};

typedef struct POINT_2D point_2d_t;
struct POINT_2D
{
    int x;
    int y;
};

typedef struct SHAPE shape_t;
struct SHAPE
{
    point_t *points;
    int count_of_points;
    edge_t *edges;
    int count_of_edges;
};

typedef struct PARAMETERS parameters_t;
struct PARAMETERS
{
    double dx = 0;
    double dy = 0;
    double dz = 0;
    double kx = 1;
    double ky = 1;
    double kz = 1;
    double angle = 0;
    char *filename;
};

int get_count_of_points(shape_t shape);
int get_count_of_edges(shape_t shape);
double get_angle(parameters_t parameters);
double get_x_index_point(shape_t &shape, int i);
double get_y_index_point(shape_t &shape, int i);
double get_z_index_point(shape_t &shape, int i);
void fill_x_index_point(shape_t &shape, int i, double x);
void fill_y_index_point(shape_t &shape, int i, double y);
void fill_z_index_point(shape_t &shape, int i, double z);
int get_first_index_edge(shape_t &shape, int i);
int get_second_index_edge(shape_t &shape, int i);
double get_x_coord_point(point_t &point);
double get_y_coord_point(point_t &point);
double get_z_coord_point(point_t &point);

shape_t init();
int free_memory(shape_t &shape);
int allocate_shape(shape_t &shape);
void free_shape(shape_t shape);

#endif // SHAPE_H
