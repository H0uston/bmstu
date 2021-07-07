#include "io.h"

/**
Формирует список элементов

@param list [in/out] - список
@param planet [in] - структура с данными

@return Возвращает OK, если ошибок не было, либо ERR_MEMORY, если не удалось выделить память
*/
int form_list(struct node **list, struct object *planet)
{
    struct object *cur = planet;
    struct node *note;

    while (cur != NULL)
    {
        note = create_list(cur);
        if (note != NULL)
            *list = add_list(*list, note);
        else
        {
            free_list(*list);
            return ERR_MEMORY;
        }

        cur = cur->next;
    }

    return OK;
}

/**
Добавляет новую запись в конец списка

@param head [in/out] - список
@param list [in] - запись

@return Возвращает указать на начало списка
*/
struct node *add_list(struct node *head, struct node *list)
{
    if (!head)
        return list;

    struct node *beg = head;
    while (head->next)
        head = head->next;
    head->next = list;

    return beg;
}

/**
Выделяется память под новую запись списка

@param data[in]

@return Возвращает указать на эту запись
*/
struct node *create_list(void *data)
{
    struct node *list = malloc(sizeof(struct node));
    if (list != NULL)
    {
        list->data = data;
        list->next = NULL;
    }

    return list;
}

/**
Считывает данные об одной планете

@param file[in] - файл, откуда будут считаны данные
@param name[in] - название планеты
@param diameter[in] - диаметр планеты

@return OK, если удалось считать данные из файла, или ERR_IO, если не удалось.
*/
int read_data(FILE *file, char *name, double *diameter)
{
    if (fscanf(file, "%80s", name) != 1)
        return ERR_IO;

    if (fscanf(file, "%lf", diameter) != 1)
        return ERR_IO;

    return OK;
}

/**
Выделяет память для записи структуры object под планету и записывает в нее данные из файла

@param name[in] - название планеты
@param diameter[in] - диаметр планеты

@return Возвращает указать на эту запись
*/
struct object *create_planet(const char *name, const double diameter)
{
    struct object *planet = malloc(sizeof(struct object));
    if (planet != NULL)
    {
        strcpy(planet->name, name);
        planet->diameter = diameter;
        planet->next = NULL;
    }

    return planet;
}

/**
Добавляет объект в структуру

@param head[in/out] - структура с данными об объектах
@param pl[in] - единичная запись

@return Возвращает указать на начало структуры
*/
struct object *add_planet(struct object *head, struct object *pl)
{
    if (!head)
        return pl;

    struct object *beg = head;
    while (head->next)
        head = head->next;
    head->next = pl;

    return beg;
}

/**
Очищает память, выделенную под список с данными

@param head[in] - структура с данными об объектах
*/
void free_struct(struct object *head)
{
    struct object *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

/**
Очищает память, выделенную под список

@param head[in] - список
*/
void free_list(struct node *head)
{
    struct node *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

/**
Считывает данные из файла и на их основе формирует структуру данных

@param file[in] - файл с данными
@param head[in/out] - структура данных

@return Возвращает OK, если не было ошибок, или ERR_MEMORY, если не удалось выделить память, или ERR_IO, если не удалось считать данные из файла.
*/
int read_from_file(FILE *file, struct object **head)
{
    char name[MAX_STR_SIZE + 1];
    double diameter;
    struct object *planet;
    *head = NULL;
    while (read_data(file, name, &diameter) == OK)
    {
        planet = create_planet(name, diameter);
        if (planet != NULL)
            *head = add_planet(*head, planet);
        else
        {
            free_struct(*head);
            return ERR_MEMORY;
        }
    }

    return OK;
}

/**
Выводит в файл данные об одной планете

@param file[in] - файл с данными
@param planet[in] - запись с данными об одной планете
*/
void print_planet(FILE *file, const struct object *planet)
{
    fprintf(file, "%s\n", planet->name);
    fprintf(file, "%lf\n", planet->diameter);
}

/**
Выводит в файл список

@param file[in] - файл с данными
@param head[in] - запись с список
*/
void print(FILE *file, struct node *head)
{
    struct node *cur = head;
    while (cur != NULL)
    {
        print_planet(file, cur->data);
        cur = cur->next;
    }
}