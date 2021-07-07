#ifndef FUNCTION_H
#define FUNCTION_H

#include "io.h"

void sum(double **matrix_a, double **matrix_b, double **matrix_c, int row, int column);

void mult(double **matrix_a, double **matrix_b, double **matrix_c, int max_i, int max_j, int max_k);

void find_minor(double **matrix, double **temp, int row, int column, int size);

int func_determinant(double **matrix, double *result, int size);

void inverse(double **matrix, double ***matrix_e, int size);

int form_matrix_e(double ***matrix_e, int size);

void find_main_element(double **matrix, double **matrix_e, int column, int size);

#endif // FUNCTION_H
