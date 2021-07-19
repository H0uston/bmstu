#ifndef IO_H
#define IO_H

#include "config.h"
#include "error.h"

void free_matrix(double **matrix, int n);

double **io_allocate_matrix(int row, int column);

int io_read_data(FILE *file, double **matrix, int row, int column);

int io_size_matrix(FILE *file, int *row, int *column);

void io_matrix_fprintf(FILE *file, double **matrix, int row, int column);

int io_form_matrix(const char *file_name, double ***matrix, int *row, int *column);

int io_matrix_out(const char *name, double **matrix, int row, int column);

#endif // IO_H
