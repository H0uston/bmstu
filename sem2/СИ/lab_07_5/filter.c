#include "filter.h"

/**

Считает сумму элементов массива.

@param array [in] массив с элементами
@param array_end [in] укаатель на "за последний" элемент

@return сумму элементов массива.
*/
int filter_sum(const int *array, const int *array_end)
{
    int sum = 0;
    while (array != array_end)
    {
        sum += *array;
        array++;
    }
    return sum;
}

/**
Считает количество элементов, удволетворяющих условию фильтра.

@param array [in] массив с элементами
@param array_end [in] указатель на "за последний" элемент массива
@param sum [in] сумма элементов массива

@return Возвращает количество элементов, удволетворяющих условию фильтра.
*/
int filter_count(const int *array, const int *array_end, int sum)
{
    int count = 0;

    while (array + 1 < array_end)
    {
        if (*array > sum - *array)
            count++;

        sum -= *array;
        array++;
    }

    return count;
}

/**
Копирует элементы массива array в массив array_filtered. Будут скопированы все элементы, удволетворяющие условию фильтра. 

@param array [in] основной массив элементов
@param array_end [in] указатель на "за последний" элемент основного массива
@param array_filtered [in] массив с некоторыми элементами основного массива, выбранными по определённым условиям задачи
@param array_filtered_end [in] указатель на "за последний" элемент "фильтрованного" массива
@param sum [in] сумма элементов массива
@param count [in] количество элементов

@return Возвращает OK, если ошибок не было, либо ERR_PARAM, если переданы неверные параметры.
*/
void filter_array(const int *array, const int *array_end, int *array_filtered, int *array_filtered_end, int sum, int count)
{
    while ((array != array_end) && (array_filtered_end != array_filtered))
    {
        sum -= *array;
        if (sum < *array)
        {
            *array_filtered = *array;
            array_filtered++;
        }
        array++;
    }
}

/**
Фильтрует массив. Возвращает новый массив.

@param array [in] основной массив элементов
@param array_end [in] указатель на "за последний" элемент основного массива
@param array_filtered [out] массив с некоторыми элементами основного массива, выбранными по определённым условиям задачи
@param array_filtered_end [out] указатель на "за последний" элемент "фильтрованного" массива

@return Возвращает OK, если ошибок не было, либо ERR_MEMORY, если возникли проблемы с выделением памяти, либо ERR_EMPTY, если массив после фильтрации оказался пустым.
*/
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int rc = OK;
    if (pb_src == NULL || pe_src == NULL || (pb_src >= pe_src))
        rc = ERR_MEMORY;

    if (rc == OK)
    {
        int sum = 0;
        sum = filter_sum(pb_src, pe_src);
 
        int count = filter_count(pb_src, pe_src, sum);

        if (count >= 1)
        {
            *pb_dst = malloc(count * sizeof(int));
            if (pb_dst)
            {
                *pe_dst = *pb_dst + count;
                filter_array(pb_src, pe_src, *pb_dst, *pe_dst, sum, count);
            }
            else
            {
                rc = ERR_MEMORY;
            }
        }
        else
        {
            rc = ERR_EMPTY;
        }
    }

    return rc;
}

