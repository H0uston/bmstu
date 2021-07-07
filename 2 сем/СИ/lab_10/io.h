//
// Created by Houston on 05/11/2018.
//

#ifndef __LAB_10_IO_H__
#define __LAB_10_IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "struct.h"

#define MAX_STR_SIZE 80

int read_data(FILE *file, char *name, double *diameter);

struct object *create_planet(const char *name, const double diameter);

struct object *add_planet(struct object *head, struct object *pl);

void free_struct(struct object *head);

int read_from_file(FILE *file, struct object **head);

void print_planet(FILE *file, const struct object *planet);

void print(FILE *file, struct node *head);

int form_list(struct node **list, struct object *planet);

struct node *add_list(struct node *head, struct node *list);

struct node *create_list(void *data);

void free_list(struct node *head);

#endif //LAB_10_IO_H
