#ifndef IO_H
#define IO_H

#include "config.h"
#include <string.h>

#define BUFFER_SIZE 70

struct list_t *form_list(FILE *file);

struct list_t *add_student(FILE *file);

void print_list(struct list_t *head);

void free_list_t(struct list_t *head);

void print_student(struct list_t *student);

#endif // IO_H
