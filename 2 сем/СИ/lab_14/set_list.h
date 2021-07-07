#ifndef LAB_14_SET_LIST_H
#define LAB_14_SET_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define OK 0
#define ERR_MEMORY (-1)

typedef int item_t;

typedef struct set_type* set_t;

set_t set_create(void);

int set_add(set_t set, item_t element);

void set_print(set_t set);

void set_free(set_t set);

bool is_in_set(set_t set, item_t element);

bool set_is_empty(set_t set);

int set_pop(set_t set, item_t element);

set_t set_union(set_t set_a, set_t set_b);

bool set_is_disjoint(set_t set_a, set_t set_b);

set_t set_intercection(set_t set_a, set_t set_b);

set_t set_difference(set_t set_a, set_t set_b);

set_t set_symmetric_difference(set_t set_a, set_t set_b);

bool set_same(set_t set_a, set_t set_b);

#endif //LAB_14_SET_LIST_H
