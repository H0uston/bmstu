#ifndef IO_H
#define IO_H

#include "config.h"

int read_data(char *file_name, int ***matrix, int *row, int *column);

void matrix_printf(int **matrix, int row, int column);

int **allocate_matrix(int row, int column);

void free_matrix(int **matrix, int row);

void array_printf(int *array, int count);

#endif // IO_H
