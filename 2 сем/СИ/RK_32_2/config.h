#ifndef CONFIG_H
#define CONFIG_H

struct list_t
{
    char *surname; // Фамилия
    char *name; // Имая
    int ent_year; // Год поступления
    int group; // Группа
    struct list_t *next;
};

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "io.h"
#include "process.h"

#define OK 0
#define ERR_CMD 1
#define ERR_FILE 2
#define ERR_MEMORY 3


#endif // CONFIG_H
