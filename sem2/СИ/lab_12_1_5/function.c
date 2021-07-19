#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR_FILE (-1)
#define ERR_MEMORY (-2)
#define ERR_EMPTY (-3)
#if TYPE != 3
#include "function.h"
#endif

// Functions of input/output
int io_count_numbers(FILE *file)
{
    int count = 0, tmp;

    while (fscanf(file, "%d", &tmp) == 1)
        count++;

    return count;
}


int io_read_array(FILE *file, int *array, int *array_end)
{
    int rc = OK;

    while (array < array_end && rc == OK)
    {
        if (fscanf(file, "%d", array) != 1)
            rc = ERR_FILE;
        array++;
    }

    return rc;
}


int io_read(FILE *file, int **array, int **array_end, int *count)
{
    int numbers_in_file, rc = OK;
    int *buffer;

    rewind(file);

    numbers_in_file = io_count_numbers(file);

    if (numbers_in_file > 0)
    {
        buffer = malloc(numbers_in_file * sizeof(int));
        if (buffer)
        {
            rewind(file);
            rc = io_read_array(file, buffer, buffer + numbers_in_file);

            if (rc != OK)
            {
                free(buffer);
                return rc;
            }

            *array = buffer;
            *count = numbers_in_file;
        }
        else
            rc = ERR_MEMORY;
    }
    else
        rc = ERR_EMPTY;

    *array_end = *array + *count;

    return rc;
}


void io_array_fprintf(FILE *file, const int *array, const int *array_end)
{
    while (array != array_end)
    {
        fprintf(file, "%d ", *array);
        array++;
    }
}


// Functions of filter
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


void filter_array(const int *array, const int *array_end, int *array_filtered, int *array_filtered_end, int sum)
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


int key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst)
{
    int count = 0;
    int sum = 0;
    if (pb_src == NULL || pe_src == NULL)
        return -1;

    sum = filter_sum(pb_src, pe_src);

    count = filter_count(pb_src, pe_src, sum);

    if (pb_dst == NULL || pe_dst == NULL || pb_dst > pe_dst)
        return count;

    if (count >= 1)
        filter_array(pb_src, pe_src, pb_dst, pe_dst, sum);

    return count;
}


// Functions of sorting
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


int sort_compare_int(const void *val1, const void *val2)
{
    int *a = (int *) val1;
    int *b = (int *) val2;
    return *a - *b;
}


int sort_compare_char(const void *val1, const void *val2)
{
    return (*(char*)val1) - (*(char*)val2);
}


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