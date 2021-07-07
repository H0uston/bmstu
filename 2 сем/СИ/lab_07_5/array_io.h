#ifndef ARRAY_IO_H
#define ARRAY_IO_H

#include "config.h"
#include "error.h"

int io_count_numbers(FILE *file);

int io_read_array(FILE *file, int *array, int *array_end);

int io_read(FILE *file, int **array, int **array_end, int *count);

void io_array_fprintf(FILE *file, const int *array, const int *array_end);

#endif // ARRAY_IO_H
