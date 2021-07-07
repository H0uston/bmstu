#include "io.h"


/**
 * Формирует список студентов
 * @param file файл с данными
 * @return указатель на начало списка
 */
struct list_t *form_list(FILE *file)
{
    struct list_t *head = add_student(file);
    if (!head)
        return NULL;

    struct list_t *tmp = head;
    struct list_t *node = add_student(file);

    while (node != NULL)
    {
        tmp->next = node;
        tmp = tmp->next;
        node = add_student(file);
    }

    return head;
}

/**
 * выводит на экран весь список студентов
 * @param head указатель на начало списка
 */
void print_list(struct list_t *head)
{
    struct list_t *tmp = head;
    while (tmp != NULL)
    {
        print_student(tmp);
        tmp = tmp->next;
    }
}

/**
 * Выводит на экран данные об одном студенте
 * @param student указатель на запись
 */
void print_student(struct list_t *student)
{
    assert(student);
    printf("'%s'\n", student->surname);
    printf("'%s'\n", student->name);
    printf("%d\n", student->ent_year);
    printf("%d\n", student->group);
}

/**
 * Выделяет память под данные и записывает сами эти данные в новую запись
 * @param file файл, откуда берутся данные
 * @return указатель на новую запись
 */
struct list_t *add_student(FILE *file)
{
    struct list_t *node = malloc(sizeof(struct list_t));
    if (!node)
        return NULL;
    node->next = NULL;

    node->surname = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!node->surname)
    {
        free(node);
        return NULL;
    }

    node->name = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!node->name)
    {
        free(node->surname);
        free(node);
        return NULL;
    }

    if (fscanf(file, "%70s", node->surname) == 1 && fscanf(file, "%70s", node->name) == 1)
    {
        if (!(fscanf(file, "%d", &node->ent_year) == 1 && fscanf(file, "%d", &node->group) == 1))
        {
            free_list_t(node);
            return NULL;
        }
        else if (node->ent_year < 0 || node->group < 0)
        {
            free_list_t(node);
            return NULL;
        }

        return node;
    }
    else
    {
        free_list_t(node);
        return NULL;
    }
}

/**
 * Освобождает память из под списка
 * @param head указатель на начало списка
 */
void free_list_t(struct list_t *head)
{
    if (head != NULL)
    {
        struct list_t *tmp = head;
        while (head)
        {
            free(head->surname);
            free(head->name);
            tmp = head->next;
            free(head);
            head = tmp;
        }
    }
}
