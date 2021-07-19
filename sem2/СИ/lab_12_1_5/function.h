#ifndef LAB_12_FUNCTION_H
#define LAB_12_FUNCTION_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR_FILE (-1)
#define ERR_MEMORY (-2)
#define ERR_EMPTY (-3)
#define ERR_CMD (-5)
#define ERR_LIB (-6)
#define ERR_FUNC (-7)

// IO functions
int io_count_numbers(FILE *file);

int io_read_array(FILE *file, int *array, int *array_end);

int io_read(FILE *file, int **array, int **array_end, int *count);

void io_array_fprintf(FILE *file, const int *array, const int *array_end);

// Filter functions
int filter_sum(const int *array, const int *array_end);

int filter_count(const int *array, const int *array_end, int sum);

void filter_array(const int *array, const int *array_end, int *array_filtered, int *array_filtered_end, int sum);

int key(const int *array, const int *array_end, int *array_filtered, int *array_filtered_end);

// Sorting functions
int sort_compare_double(const void *val1, const void *val2);

int sort_compare_int(const void *val1, const void *val2);

int sort_compare_char(const void *val1, const void *val2);

void sort_swap(void *a, void *b, size_t size);

void mysort(void *base, size_t nmemb, size_t size, int (*compare)(const void*, const void*));

#endif //LAB_12_FUNCTION_H
