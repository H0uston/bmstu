#include "function.h"

/**
Сравнивает числа типа double

@param val1[in] - указатель на запись структуры
@param val2[in] - указатель на запись структуры

@return 1, если первое число больше второго, -1, если иначе, или 0, если числа равны
*/
int compare_double(const void *val1, const void *val2)
{
    const struct object *p1 = val1;
    const struct object *p2 = val2;
    if (fabs(p1->diameter - p2->diameter) > EPS && p1->diameter > p2->diameter)
        return 1;
    if (fabs(p1->diameter - p2->diameter) > EPS && p1->diameter < p2->diameter)
        return -1;
    return 0;
}

/**
Сравнивает строки

@param val1[in] - указатель на запись структуры
@param val2[in] - указатель на строку

@return 1, если строки не равны, или 0, если числа равны
*/
int compare_string(const void *val1, const void *val2)
{
    const struct object *p1 = val1;
    if (strcmp((char *) p1->name, (char *) val2) == 0)
        return 0;

    return 1;
}

/**
Производит поиск элемента списка

@param head[in] - список
@param data[in] - указатель на строку
@param comparator[in] - функция сравнения

@return NULL, если не удалось найти элемент, или указатель, если запись нашлась
*/
node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void *))
{
    if (head == NULL || data == NULL || comparator == NULL)
        return NULL;

    for (struct node *cur = head; cur != NULL; cur = cur->next)
    {
        if (comparator(cur->data, data) == 0)
            return cur;
    }
    return NULL;
}

/**
Производит удаление элемента из списка

@param head[in/out] - список

@return NULL, если список пуст, или указатель на удаленный из списка элемент
*/
void *pop_back(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;

    void *pointer;
    if ((*head)->next == NULL)
    {
        pointer = (*head)->data;
        free(*head);
        *head = NULL;
    }
    else
    {
        struct node *cur;
        for (cur = *head; cur->next->next; cur = cur->next);
        pointer = (void *)cur->next->data;
        free(cur->next);
        cur->next = NULL;
    }

    return pointer;
}

/**
Производит связывание двух списков

@param head_a[in/out] - список
@param head_b[in/out] - список
*/
void append(node_t **head_a, node_t **head_b)
{
    if ((*head_a) == NULL && (*head_b) != NULL)
    {
        (*head_a) = *head_b;
        *head_b = NULL;
    }
    else if (*head_a != NULL && *head_b != NULL)
    {
        struct node *cur_a = *head_a;

        while (cur_a->next != NULL)
            cur_a = cur_a->next;

        cur_a->next = *head_b;
        *head_b = NULL;
    }
}

/**
Производит сортировку списка

@param head[in/out] - список
*/
void insertion_sort(node_t **head)
{
    struct node *sorted_list = NULL;
    struct node *cur = *head;
    struct node *next;

    while (cur != NULL)
    {
        next = cur->next;
        sorted_insert(&sorted_list, cur, compare_double);
        cur = next;
    }

    *head = sorted_list;
}

/**
Производит сортировку списка

@param head[in/out] - список
@param element[in] - указатель на неотсортированный элемент списка
@param comparator[in] - функция сравнения
*/
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void*, const void *))
{
    // Если текущий элемент отсортированного списка больше элемента неотсортированного, то добавляет его в начало
    if (*head == NULL || comparator((*head)->data, element->data) > 0)
    {
        element->next = *head;
        *head = element;
    }
    else
    {
        struct node *cur = *head;
        // Пока следующий за текущим элемент списка меньше элемента неотсортированного, идет по списку. Если элемент неотсортированного
        // самый большой, добавляет в конец.
        while (cur->next != NULL && comparator(cur->next->data, element->data) < 0)
            cur = cur->next;
        element->next = cur->next;
        cur->next = element;
    }
}
