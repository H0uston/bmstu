#ifndef INPUT_POINT_H
#define INPUT_POINT_H

#include "config.h"
#include "shape.h"
#include "stream.h"

int read_edges_from_file(edge_t *edges, int count_of_edges, stream_t &stream);
int read_points_from_file(point_t *points, int count_of_points, stream_t &stream);
int read_counts_from_file(int *count_of_points, int *count_of_edges, stream_t &stream);
int read_edges(edge_t *edges, FILE *file, int i);
int read_points(point_t *points, FILE *file, int i);
int read_counts(FILE *file, int &count_of_points, int &count_of_edges);

#endif // INPUT_POINT_H
