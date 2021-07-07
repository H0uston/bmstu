#ifndef SORT_H
#define SORT_H

#include "config.h"
#include "error.h"
#include <assert.h>

int sort_compare_double(const void *val1, const void *val2);

int sort_compare_int(const void *val1, const void *val2);

int sort_compare_char(const void *val1, const void *val2);

void sort_swap(void *a, void *b, size_t size);

void mysort(void *base, size_t nmemb, size_t size, int (*compare)(const void*, const void*));

#endif // SORT_H
