#include "set_array.h"

struct set_type
{
    item_t *head;
    int size;
};

/**
 * Выделаяет память под структуру множества
 * @return NULL, если произошла ошибка, или указатель на множество
 */
set_t set_create(void)
{
    set_t set = malloc(sizeof(struct set_type));

    if (set)
    {
        set->head = NULL;
        set->size = 0;
    }

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

    item_t *tmp = realloc(set->head, (set->size + 1) * sizeof(item_t));
    if (!tmp)
        return ERR_MEMORY;
    set->head = tmp;
    set->head[set->size] = element;
    set->size++;

    return OK;
}

/**
 * Печатает элементы множества
 * @param set[in] - множество
 */
void set_print(set_t set)
{
    for (int i = 0; i < set->size; i++)
        printf("%d ", (int)set->head[i]);
}

/**
 * Освобождает память из под множества
 * @param set[in] - множество
 */
void set_free(set_t set)
{
    free(set->head);

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
    for (int i = 0; i < set->size; i++)
        if (set->head[i] == element)
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
    return set->size == 0;
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
        return OK;
    else if (!is_in_set(set, element))
        return OK;
    else
    {
        for (int i = 0; i < set->size; i++)
        {
            if (set->head[i] == element)
            {
                set->head[i] = set->head[set->size - 1];
                break;
            }
        }

        item_t *tmp = realloc(set->head, (set->size - 1) * sizeof(item_t));
        if (!tmp)
            return ERR_MEMORY;
        set->head = tmp;
        set->size--;
    }

    return OK;
}

/**
 * Объединяет множества
 * @param set_a[in] - множество
 * @param set_b[in] - множество
 * @return Возвращает множество или NULL, если произошла ошибка выделения памяти
 */
set_t set_union(set_t set_a, set_t set_b)
{
    set_t set_c = set_create();
    if (!set_c)
        return NULL;

    int rc = OK;
    for (int i = 0; rc == OK && i < set_a->size; i++)
        rc = set_add(set_c, set_a->head[i]);

    for (int i = 0; rc == OK && i < set_b->size; i++)
        rc = set_add(set_c, set_b->head[i]);

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
    for (int i = 0; i < set_a->size; i++)
    {
        for (int j = 0; j < set_b->size; j++)
        {
            if (set_a->head[i] == set_b->head[j])
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

    int rc = OK;
    for (int i = 0; rc == OK && i < set_a->size; i++)
    {
        if ((is_in_set(set_b, set_a->head[i])))
            rc = set_add(set_c, set_a->head[i]);
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
 * @return Возвращает множество или NULL, если произошла ошибка выделения памяти
 */
set_t set_difference(set_t set_a, set_t set_b)
{
    set_t set_c = set_create();
    if (!set_c)
        return NULL;
    int rc = OK;
    for (int i = 0; rc == OK && i < set_a->size; i++)
    {
        if (!(is_in_set(set_b, set_a->head[i])))
            rc = set_add(set_c, set_a->head[i]);
    }

    if (rc == OK)
        return set_c;
    else
        return NULL;
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
    {
        set_free(set_c);
        return NULL;
    }

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
    if ((flag = (set_a->size == set_b->size)))
    {
        for (int i = 0; flag && i < set_a->size; i++)
            flag = is_in_set(set_b, set_a->head[i]);
    }

    return flag;
}

