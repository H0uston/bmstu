#ifndef FUNCTION_H
#define FUNCTION_H

#include "config.h"
#define BUFFER_SIZE 128

int read_data(FILE *file, char **result, size_t *result_size, size_t *count_row);

int find_count_column(const char *string, const size_t count_row, size_t *count_column);

#endif // FUNCTION_H
