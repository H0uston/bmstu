#ifndef __LAB_10_FUNCTION_H__
#define __LAB_10_FUNCTION_H__

#include <math.h>

#include "struct.h"
#include "config.h"

#define EPS 0.0001

int compare_double(const void *val1, const void *val2);

int compare_string(const void *val1, const void *val2);

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void *));

void *pop_back(node_t **head);

void append(node_t **head_a, node_t **head_b);

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void*, const void *));

void insertion_sort(node_t **head);

#endif //LAB_10_FUNCTION_H
