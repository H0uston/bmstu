#ifndef FILTER_H
#define FILTER_H

#include "config.h"
#include "error.h"

int filter_sum(const int *array, const int *array_end);

int filter_count(const int *array, const int *array_end, int sum);

void filter_array(const int *array, const int *array_end, int *array_filtered, int *array_filtered_end, int sum, int count);

int key(const int *array, const int *array_end, int **array_filtered, int **array_filtered_end);
#endif // FILTER_H
