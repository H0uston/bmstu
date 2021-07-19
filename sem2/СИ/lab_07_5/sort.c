#include "sort.h"

/**
Сравнивает элементы типа double.

@param val1 [in]
@param val2 [in]

Возвращает 1, если val1 > val2, возвращает -1, если val1 < val2. Если равны, то возвращает 0.
*/
int sort_compare_double(const void *val1, const void *val2)
{
    double *a = (double *) val1;
    double *b = (double *) val2;
    if (*a > *b) 
        return 1;
    if (*a < *b)
        return -1;
    return 0;
}

/**
Сравнивает элементы типа int.

@param val1 [in]
@param val2 [in]

Возвращает положительное значение, если val1 > val2, возвращает отрицательное значение, если val1 < val2. Если равны, то возвращает 0.
*/
int sort_compare_int(const void *val1, const void *val2)
{
    int *a = (int *) val1;
    int *b = (int *) val2;
    return *a - *b;
}

/**
Сравнивает элементы типа double.

@param val1 [in]
@param val2 [in]

Возвращает положительное значение, если val1 > val2, возвращает отрицательное значение, если val1 < val2. Если равны, то возвращает 0.
*/
int sort_compare_char(const void *val1, const void *val2)
{
    return (*(char*)val1) - (*(char*)val2);
}

/**
Меняет местами элементы массива.

@param a [out]
@param b [out]
@param size [in]
*/
void sort_swap(void *a, void *b, size_t size)
{
    char *pos_a = a;
    char *pos_b = b;
    char buffer;
    for (size_t i = 0; i < size; i++)
    {
        buffer = *pos_a;
        *pos_a = *pos_b;
        *pos_b = buffer;
        pos_a++;
        pos_b++;
    }
}

/**
Сортирует массив методом пузырька.

@param base [out]
@param nmemb [in]
@param size [in]
@param compare [function]
*/
void mysort(void *base, size_t nmemb, size_t size, int (*compare)(const void*, const void*))
{
    char *after_last = (char*)base + nmemb * size;
    char *last = after_last - size;
    while ((char*)base < last)
    {
        for (char *pos = base; pos < last; pos += size)
            if (compare(pos, (pos + size)) > 0)
                sort_swap(pos, (pos + size), size);
        // Сдвиг правой границы массива
        last -= size;

        for (char *pos = last; pos > (char*)base; pos -= size)
            if (compare((pos - size), pos) > 0)
                sort_swap(pos, (pos - size), size);
        // Сдвиг левой границы массива
        base = (char*)base + size;
    }
}
