//
// Created by Houston on 21/10/2018.
//

#include "my_string.h"

/**
Вычисляет количество символов в строке (символ окончания строки не учитывается).

@param str [in] - строка

@return Размер строки
*/

size_t len(const char *str)
{
    size_t i = 0;
    if (str == NULL)
        return i;
    
    while (str[i] != '\0')
        i++;
    return i;
}

/**
Сравнивает две строки

@param name [in] - строка
@param matrix [in] - строка

@return Возвращает true, если строки одинаковые, false, если нет
*/
int str_compare(const char *str_a, const char *str_b)
{
    int size_str_a = len(str_a);
    int size_str_b = len(str_b);
    if (size_str_a == size_str_b)
    {
        for (int i = 0; i < size_str_a; i++)
        {
            if (str_a[i] != str_b[i])
                return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

/**
Ищет подстроку substring в строке string

@param string [in] - строка
@param substring [in] - подстрока

@return Возвращает указатель на начало подстроки в строке
*/
char *find(const char *string, const char *substring)
{
    size_t len_string = len(string);
    size_t len_substring = len(substring);
    for (int i = 0; i < len_string; i++)
    {
        if (string[i] == substring[0])
        {
            int flag = 0;
            int j;
            for (j = 0; (j < len_substring) && ((i + j) < len_string) && flag == 0; j++)
            {
                if (substring[j] != string[i + j])
                    flag = 1;
            }
            if ((flag == 0) && (j == len_substring))
                return (char *)string + i;
        }
    }
    return NULL;
}

/**
Копирует из buf в str (аналог strcpy)

@param str [out] - строка
@param buf [in] - строка

@return Возвращает скопированную строку
*/
char *my_strcpy(char *str, const char *buf)
{
    size_t size = len(buf);
    for (int i = 0; i < size; i++)
        str[i] = buf[i];

    str[size] = '\0';
    return str;
}

/**
Копирует из buf в str до индекса end_index

@param str [out] - строка
@param buf [in] - строка
@param end_index [in] - конечный индекс

@return Возвращает скопированную строку
*/
char *str_copy_n(char *str, const char *buf, int end_index)
{
    size_t size_buf = len(buf);
    size_t end;
    if (size_buf < end_index)
        end = size_buf;
    else
        end = end_index;

    for (int i = 0; i < end; i++)
        str[i] = buf[i];
    str[end] = '\0';

    return str;
}
