#include "set_list.h"

struct node
{
    item_t value;
    struct node *next;
};

struct set_type
{
    struct node *head;
};

/**
 * Выделаяет память под структуру множества
 * @return NULL, если произошла ошибка, или указатель на множество
 */
set_t set_create(void)
{
    set_t set = malloc(sizeof(set_t));

    if (set)
        set->head = NULL;

    return set;
}

/**
 * Добавляет элемент во множество
 * @param set[in/out] - множество
 * @param element[in] - элемент
 * @return ERR_MEMORY, если не удалось выделить память, или OK
 */
int set_add(set_t set, item_t element)
{
    if (is_in_set(set, element))
        return OK;

    struct node *node = malloc(sizeof(struct node));
    if (!node)
        return ERR_MEMORY;

    node->next = NULL;
    node->value = element;
    if (set->head == NULL)
        set->head = node;
    else
    {
        struct node *list = set->head;
        while (list->next)
            list = list->next;
        list->next = node;
    }

    return OK;
}

/**
 * Печатает элементы множества
 * @param set[in] - множество
 */
void set_print(set_t set)
{
    struct node *list = set->head;
    for (; list; list = list->next)
        printf("%d ", (int)list->value);
}

/**
 * Освобождает память из под множества
 * @param set[in] - множество
 */
void set_free(set_t set)
{
    struct node *list = set->head;
    struct node *next;
    while (list)
    {
        next = list->next;
        free(list);
        list = next;
    }

    free(set);
}

/**
 * Проверяет содержит ли множество set элемент element
 * @param set[in] - множество
 * @param element[in] - элемент
 * @return true, если содержит, иначе false
 */
bool is_in_set(set_t set, item_t element)
{
    struct node *list = set->head;

    for (; list; list = list->next)
        if (list->value == element)
            return true;

    return false;
}

/**
 * Проверяет пусто ли множество
 * @param set[in] - множество
 * @return true, если пусто, иначе false
 */
bool set_is_empty(set_t set)
{
    return set->head == NULL;
}

/**
 * Удаляет из множества set элемент element
 * @param set[in/out] - множество
 * @param element[in] - элемент
 * @return ERR_MEMORY, если не удалось перевыделить память, или OK
 */
int set_pop(set_t set, item_t element)
{
    if (set_is_empty(set))
        return ERR_MEMORY;
    else if (!is_in_set(set, element))
        return OK;
    else
    {
        struct node *list = set->head;
        struct node *to_delete;
        if (list->value == element)
        {
            set->head = list->next;
            free(list);
        }
        else
        {
            for (; list->next; list = list->next)
            {
                if (list->next->value == element)
                {
                    to_delete = list->next;
                    list->next = list->next->next;
                    free(to_delete);
                    break;
                }
            }
        }
    }

    return OK;
}

/**
 * Объединяет множества
 * @param set_a[in/out] - множество
 * @param set_b[in] - множество
 * @return Возвращает множество или NULL, если произошла ошибка выделения памяти
 */
set_t set_union(set_t set_a, set_t set_b)
{
    set_t set_c = set_create();
    if (!set_c)
        return NULL;

    struct node *list_a = set_a->head;
    struct node *list_b = set_b->head;
    int rc = OK;
    for (; rc == OK && list_a; list_a = list_a->next)
        rc = set_add(set_c, list_a->value);

    for (; rc == OK && list_b; list_b = list_b->next)
        rc = set_add(set_c, list_b->value);

    if (rc == OK)
        return set_c;
    else
        return NULL;
}

/**
 * Проверяет содержат ли множества общие элементы
 * @param set_a[in] - множество
 * @param set_b[in] - множество
 * @return true, если множества не имеют общих элементов.
 */
bool set_is_disjoint(set_t set_a, set_t set_b)
{
    struct node *list_a = set_a->head;
    struct node *list_b = set_b->head;
    for (; list_a; list_a = list_a->next)
    {
        for (struct node *cur = list_b; cur; cur = cur->next)
        {
            if (list_a->value == cur->value)
                return false;
        }
    }

    return true;
}

/**
 * Производит пересечение множеств
 * @param set_a[in/out] - множество
 * @param set_b[in] - множество
 * @return Возвращает множество или NULL, если произошла ошибка выделения памяти
 */
set_t set_intercection(set_t set_a, set_t set_b)
{
    set_t set_c = set_create();
    if (!set_c)
        return NULL;

    struct node *list_a = set_a->head;
    int rc = OK;
    for (; rc == 0 && list_a; list_a = list_a->next)
    {
        if ((is_in_set(set_b, list_a->value)))
            rc = set_add(set_c, list_a->value);
    }

    if (rc == OK)
        return set_c;
    else
        return NULL;
}

/**
 * Производит разность множеств
 * @param set_a[in/out] - множество
 * @param set_b[in] - множество
 * @return ERR_MEMORY, если не удалось перевыделить память, или OK
 */
set_t set_difference(set_t set_a, set_t set_b)
{
    set_t set_c = set_create();
    if (!set_c)
        return NULL;

    struct node *list_a = set_a->head;
    int rc = OK;
    for (; rc == 0 && list_a; list_a = list_a->next)
    {
        if (!(is_in_set(set_b, list_a->value)))
            rc = set_add(set_c, list_a->value);
    }

    if (rc == OK)
        return set_c;
    else
        return NULL;
}

/**
 * Считает количество элементов во множестве
 * @param set[in] - множество
 * @return число элементов
 */
static int len(set_t set)
{
    int count = 0;
    struct node *list = set->head;
    for (; list; list = list->next)
        count++;

    return count;
}

/**
 * Производит симметричную разность множеств
 * @param set_a[in/out] - множество
 * @param set_b[in] - множество
 * @return Возвращает множество или NULL, если произошла ошибка выделения памяти
 */
set_t set_symmetric_difference(set_t set_a, set_t set_b)
{
    set_t set_c = set_union(set_a, set_b);
    if (!set_c)
        return NULL;

    set_t set_d = set_intercection(set_a, set_b);
    if (!set_d)
        return NULL;

    set_t set_e = set_difference(set_c, set_d);
    set_free(set_d);
    set_free(set_c);
    return set_e;
}

/**
 * Проверяет равны ли множества
 * @param set_a[in] - множество
 * @param set_b[in] - множество
 * @return true, если множества одинаковы.
 */
bool set_same(set_t set_a, set_t set_b)
{
    bool flag;
    if ((flag = (len(set_a) == len(set_b))))
    {
        for (struct node *list = set_a->head; flag && list; list = list->next)
            flag = is_in_set(set_b, list->value);
    }

    return flag;
}
