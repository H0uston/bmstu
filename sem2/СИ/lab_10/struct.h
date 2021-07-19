#ifndef __LAB_10_STRUCT_H__
#define __LAB_10_STRUCT_H__

#define MAX_STR_SIZE 80

typedef struct object planet_t;

struct object
{
    // Название объекта
    char name[MAX_STR_SIZE + 1];
    // Диаметр объекта
    double diameter;
    planet_t *next;
};

typedef struct node node_t;

struct node
{
    // Указатель на объект списка
    void *data;
    node_t *next;
};

#endif //LAB_10_STRUCT_H
