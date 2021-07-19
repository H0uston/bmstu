#ifndef FUNCTION_H
#define FUNCTION_H

#include "config.h"
void swap_elements(int **matrix, int row, int column);

double find_min(int **matrix, int row, int column);

int find_count_of_min(int **matrix, int row, int column, int min);

void fill_array(int **matrix, int row, int column, int *array, int min);

#endif // FUNCTION_H
