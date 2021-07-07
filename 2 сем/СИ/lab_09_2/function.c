#include "function.h"
#include <unistd.h>

/**
Считывает строку в переменную result через fgets по buffer_size* символов из файла file

@param lineptr [in] - строка
@param n [in] - буфер
@param stream [in] - файл

@return Возвращает считанную строку
*/
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    if (lineptr == NULL || n == NULL || stream == NULL)
    {
        return NONE;
    }

    if (*n == 0)
        *lineptr = NULL;

    size_t buffer_size = 128;
    char buffer[buffer_size];
    ssize_t size_line = 0;
    int readed;
    char *tmp = NULL;
    while (fgets(buffer, buffer_size, stream))
    {
        // printf("\nBuffer: '%s'", buffer);
        readed = len(buffer);
        // Memory expansion
        if (size_line + readed + 1 > *n || *lineptr == NULL)
        {
            size_t new_size = size_line + readed + 1;

            tmp = realloc(*lineptr, new_size);
            if (!tmp)
                return NONE;
            else
            {
                *n = new_size;
                *lineptr = tmp;
            }
        }

        str_copy_n((char *)(*lineptr + size_line), buffer, readed);
        size_line += readed;
        if ((*lineptr)[size_line - 1] == '\n')
        {
            (*lineptr)[size_line] = '\0';
            break;
        }
    }

    if (size_line == 0)
        return NONE;

    return size_line;
}
/**
Заменяет подстроку search подстрокой replace в строке source

@param source [in] - строка
@param search [in] - подстрока, которая будет заменена
@param replace [in] - подстрока, которой будет заменена подстрока search

@return строка с заменёнными подстроками
*/
char *str_replace(const char *source, const char *search, const char *replace)
{
    if (source == NULL || search == NULL || replace == NULL)
        return NULL;

    size_t size_replace = len(replace);
    size_t size_search = len(search);
    size_t size_source = len(source);

    size_t count_search = 0; // Количество найденных подстрок для замены
    const char *str_tmp_a;
    const char *str_tmp_b;

    // Идём по исходной строке, считая замены
    for (str_tmp_a = source; (str_tmp_b = find(str_tmp_a, search)); str_tmp_a = str_tmp_b + size_search)
        count_search++;

    // Размер результирующей строки
    size_t size_result = size_source + count_search * (size_replace - size_search);
    char *result = (char *) malloc((size_result + 1) * sizeof(char));

    if (result != NULL)
    {
        char *str_tmp = result;
        size_t size_skip; // Количество символов между заменяемыми подстроками
        for (str_tmp_a = source; (str_tmp_b = find(str_tmp_a, search)); str_tmp_a = str_tmp_b + size_search)
        {
            size_skip = str_tmp_b - str_tmp_a; // Количество символов до заменяемой подстроки, которое нужно перенести без изменений
            str_copy_n(str_tmp, str_tmp_a, size_skip);
            str_tmp += size_skip;
            str_copy_n(str_tmp, replace, size_replace); // На место искомой строки вставляем подстроку, на которую нужно заменить
            str_tmp += size_replace;
        }
        my_strcpy(str_tmp, str_tmp_a); // Копируем в результирующую строку ту часть строки, которая находилась за последней заменой
    }
    return result;
}
