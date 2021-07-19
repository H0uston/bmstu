#include "array_io.h"

/**
Считает количество элементов в файле.

@param file [in] файл, элементы которого считаются

@return Возвращает количество элементов в файле.
*/
int io_count_numbers(FILE *file)
{
    int count = 0, tmp;

    while (fscanf(file, "%d", &tmp) == 1)
        count++;

    return count;
}

/**
Считывает из файла count элементов и записывает их в массив array.

@param file [in] файл, из которого считываются элементы
@param array [out] массив, в который записываются элементы из файла
@param array_end [in] указатель на "за последний" элемент массива

@return Возвращает OK, если ошибок не было, либо ERR_FILE, если переданы неверные данные.
*/
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

/**
Считывает данные из файла в массив, создает указатель на "за последний" элемент. 

@param file [in] файл, с данными
@param array [out] массив, в который записываются элементы из файла
@param array_end [out] указатель на "за последний" элемент
@param count [out] число элементов в файле

@return Возвращает OK, если ошибок не было, либо ERR_EMPTY, если файл пустой, либо ERR_MEMORY, если возникли проблемы с памятью.
*/
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

/**
Выводит элементы массива в file.

@param file [in] файл, в который будут записываться данные из массива
@param array [in] массив с элементами
@param array_end [in] указатель на "за последний" элемент массива
*/
void io_array_fprintf(FILE *file, const int *array, const int *array_end)
{
    while (array != array_end)
    {
        fprintf(file, "%d ", *array);
        array++;
    }
}
