#include <stdio.h>
#include <stdbool.h>

/**
 * Производит сдвиг элементов массива
 * @param array[in/out] - массив
 * @param n[in] - размер массива
 * @param k[in] - на какое количество элементов нужно сдвинуть
 * @return 0, если все параметры верны, -1, если есть ошибка
 */
int shift_array(int *array, int n, int k)
{
    if (array == NULL || k < 0 || n <= 0)
        return (-1);
    int tmp;
    if (k > n)
        k %= n;

    // Переворачивает все элементы до k
    for (int i = 0; i < k / 2; i++)
    {
        tmp = array[i];
        array[i] = array[k - i - 1];
        array[k - i - 1] = tmp;
    }

    // Переворачивает все элементы после k
    for (int i = k; i < (k + (n - k) / 2); i++)
    {
        tmp = array[i];
        array[i] = array[n - (i - k) - 1];
        array[n - (i - k) - 1] = tmp;
    }

    // Переворачивает весь массив
    for (int i = 0; i < n / 2; i++)
    {
        tmp = array[i];
        array[i] = array[n - i - 1];
        array[n - i - 1] = tmp;
    }

    return 0;
}

/**
 * Проверяет является ли число полным квадратом
 * @param n[in] - число
 * @return true - да, false - нет
 */
bool is_square(int n)
{
    int i = 1;
    while (n > 0)
    {
        n -= i;
        i += 2;
    }
    return n == 0;
}

/**
 * Считает количество полных квадратов в массиве
 * @param array[in] - массив
 * @param n[in] - размер массива
 * @return число полных квадратов
 */
int count_square(const int *array, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        if (is_square(array[i]))
            count++;
    return count;
}

/**
 * Заносит из array в array_filtered все полные квадраты
 * @param array[in] - массив
 * @param array_filtered[in/out] - массив с полными квадратами
 * @param n[in] - размер массива array
 * @param size_filtered[in/out] - размер массива с полными квадратами
 * @return возвращает количество полных квадратов в array или -1, если переданные параметры неверны
 */
int filter_square(const int *array, int *array_filtered, int n, int *size_filtered)
{
    if (array == NULL || n <= 0 || size_filtered == NULL)
        return -1;
    int count = count_square(array, n);

    if (count > *size_filtered || *size_filtered < 0 || array_filtered == NULL)
    {
        *size_filtered = count;
        return -1;
    }

    *size_filtered = count;
    int j = 0;
    for (int i = 0; i < n && j < count; i++)
        if (is_square(array[i]))
        {
            array_filtered[j] = array[i];
            j++;
        }


    return 0;
}

