//
// Created by Houston on 18/11/2018.
//

#include "function.h"
#include <stdlib.h>

/**
Считает количество символов в строке

@param str [in] - строка

@return количество символов в строке
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
Копирует из buf в str end_index символов

@param str [in/out] - строка
@param buf [in] - строка
@param end_index [in] - количество символов, которое нужно скопировать

@return указатель на str
*/
char *my_strncpy(char *str, const char *buf, int end_index)
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

/**
Переводит число в восьмиричную систему счисления

@param result [in] - строка, содержащая число в восьмеричной сс
@param num [in] - число

*/
void make_octal(char *result, unsigned int num)
{
    if (num == 0)
    {
        result[0] = '0';
        result[1] = '\0';
    }
    else
    {
        int length = int_len(num, OCTAL_BASE);
        unsigned int rem = 0;
        int i = 0;
        while (num != 0)
        {
            rem = num % OCTAL_BASE;
            result[length - i - 1] = rem + '0';
            num /= OCTAL_BASE;
            i++;
        }
        result[length] = '\0';
    }
}

/**
Считает количество разрядов в числе

@param num [in] - число
@param base [in] - система счисления

@return количество разрядов
*/
size_t int_len(long int number, int base)
{
    if (number == 0)
        return 1;

    size_t length = 0;

    if (number < 0)
    {
        number *= (-1);
        length++;
    }

    while (number)
    {
        length++;
        number /= base;
    }

    return length;
}

/**
Печатает число в строку

@param s [in/out] - указатель на результирующую строку
@param n [in] - количество байт, которое можно записать в результирующую строку
@param number [in] - число, которое будет записано
*/
void printf_number(char *s, long int number, int n)
{
    int end = int_len(number, DECIMAL_BASE);

    unsigned long long rem = 0;
    unsigned long long digits;

    if (number < 0)
        digits = -number;
    else
        digits = number;

    for (int i = end; i; i--)
    {
        rem = digits % DECIMAL_BASE;
        if (i <= n) // Записывает только первые разряды, если маленькое n
            s[i - 1] = rem + '0';
        digits /= DECIMAL_BASE;
    }

    if (number < 0)
        s[0] = '-';
}

/**
Функция форматирования строки

@param s [in/out] - указатель на результирующую строку
@param n [in] - количество байт, которое можно записать в результирующую строку
@param format [in] - необработанная строка
@param ... [in] - значения для спецификаторов

@return количество байт, которое необходимо, чтобы обработать строку до конца
*/
int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    if (format == NULL)
        return -1;

    long int decimal_int;
    char *str = NULL;
    int length;
    va_list params;
    va_start(params, format);

    int fi,sj; // fi == format_i and sj == string_j
    for (fi = 0, sj = 0; format[fi]; fi++)
    {
        if (format[fi] != '%')
        {
            if (sj + 1 < n)
                s[sj] = format[fi];
            sj++;
        }
        else if (format[fi + 1])
        {
            switch(format[fi + 1])
            {
                case 's': // string
                {
                    str = va_arg(params, char *);

                    if (sj + 1 < n)
                        my_strncpy(s + sj, str, n - sj - 1);
                    sj += len(str);

                    fi++;
                    break;
                }
                case 'o': // octal number
                {
                    decimal_int = va_arg(params, unsigned);
                    length = int_len(decimal_int, OCTAL_BASE);
                    char octal_num[length];
                    make_octal(octal_num, decimal_int);

                    if (sj + 1 < n)
                        my_strncpy(s + sj, octal_num, n - sj - 1);

                    sj += len(octal_num);

                    fi++;
                    break;
                }
                case 'l':// long decimal number
                {
                    if (format[fi + 2] && format[fi + 2] == 'd')
                    {
                        decimal_int = va_arg(params, long int);

                        if (sj + 1 < n)
                            printf_number(s + sj, decimal_int, n - sj - 1);

                        sj += int_len(decimal_int, DECIMAL_BASE);

                        fi += 2;
                    }
                    break;
                }
                default:
                {
                    s[sj] = '%';
                    sj++;
                }
            }
        }
    }

    if (s != NULL)
        s[sj] = '\0';

    return sj;
}
