/* strrchr - Функция ищет последнее вхождение символа symbol в строку string.
 * Возвращает указатель на последнее вхождение символа в строке string.
 * Завершающий нулевой символ считается частью строки.
 * Таким образом, он также может быть найден для получения указателя на конец строки.
 * */
/* strdup - Функция дублирует строку, на которую указывает аргумент str.
 * Память под дубликат строки выделяется с помощью функции malloc,
 * и по окончанию работы с дубликатом должна быть очищена с помощью функции free.
 * */
#include "function.h"

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

char *my_strrchr(const char *string, int symbol)
{
    const char *pointer = NULL;
    int i = 0;
    while (string[i] != '\0')
    {
        if (symbol == string[i])
            pointer = &string[i];
        i++;
    }

    if (symbol == '\0')
        pointer = &string[i];

    return (char *)pointer;
}

char *my_strdup(const char *string_a)
{
    char *string_b = NULL;
    string_b = malloc(len(string_a) + 1);
    if (string_b)
    {
        int i = 0;
        while (string_a[i] != '\0')
        {
            string_b[i] = string_a[i];
            i++;
        }
        string_b[i] = '\0';
    }

    return string_b;
}
