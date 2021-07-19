//
// Created by Houston on 18/11/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "function.h"

int my_strcmp(const char *str_a, const char *str_b)
{
    size_t size_str_a = len(str_a);
    size_t size_str_b = len(str_b);
    if (size_str_a == size_str_b)
    {
        for (int i = 0; i < size_str_a; i++)
        {
            if (str_a[i] != str_b[i])
                return 1;
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

void test_snprintf(void)
{
    int error_count = 0;
    int i = 1;

    // 1-й тест. Нет замен.
    {
        char string[15] = "";
        char string_r[15] = "";
        size_t len_buffer = 14;
        size_t len_buffer_r = 14;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "Night in June");
        value = my_snprintf(string, len_buffer, "Night in June");
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;
    // 2-й тест. Замена одной строки.
    {
        char string[10] = "";
        char string_r[10] = "";
        size_t len_buffer = 4;
        size_t len_buffer_r = 4;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "%s", "one");
        value = my_snprintf(string, len_buffer, "%s", "one");
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;
    // 3-й тест. Замена одного числа.
    {
        char string[10] = "";
        char string_r[10] = "";
        size_t len_buffer = 5;
        size_t len_buffer_r = 5;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "%o", 157);
        value = my_snprintf(string, len_buffer, "%o", 157);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;
    // 4-й тест. Замена строки в строке.
    {
        char string[20] = "";
        char string_r[20] = "";
        size_t len_buffer = 19;
        size_t len_buffer_r = 19;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "My name is %s", "Evgeniy");
        value = my_snprintf(string, len_buffer, "My name is %s", "Evgeniy");
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;
    // 5-й тест. Замена числа в строке.
    {
        char string[20] = "";
        char string_r[20] = "";
        size_t len_buffer = 19;
        size_t len_buffer_r = 19;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "Who is %o", 23);
        value = my_snprintf(string, len_buffer, "Who is %o", 23);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;
    // 6-й тест. Снчала замена потом строка
    {
        char string[20] = "";
        char string_r[20] = "";
        size_t len_buffer = 19;
        size_t len_buffer_r = 19;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "%s is bad day", "monday");
        value = my_snprintf(string, len_buffer, "%s is bad day", "monday");
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;
    // 7-й тест. Сначала замена потом строка.
    {
        char string[20] = "";
        char string_r[20] = "";
        size_t len_buffer = 19;
        size_t len_buffer_r = 19;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "%o - what?", 23);
        value = my_snprintf(string, len_buffer, "%o - what?", 23);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;
    // 8-й тест. Замена со строкой и числом.
    {
        char string[30] = "";
        char string_r[30] = "";
        size_t len_buffer = 29;
        size_t len_buffer_r = 29;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "It's a %s to say %o", "hard", 0);
        value = my_snprintf(string, len_buffer, "It's a %s to say %o", "hard", 0);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;

    // 9-й тест. Замена с числом и строкой.
    {
        char string[30] = "";
        char string_r[30] = "";
        size_t len_buffer = 15;
        size_t len_buffer_r = 15;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer_r, "It's a %o to say %s", 1215, "hard");
        value = my_snprintf(string, len_buffer, "It's a %o to say %s", 1215, "hard");
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;

    // 10-й тест. Замена с десятичным числом и строкой.
    {
        char string[18] = "";
        char string_r[18] = "";
        size_t len_buffer = 17;
        size_t len_buffer_r = 17;
        int value;
        int value_r;
        long int num = 1;
        value_r = snprintf(string_r, len_buffer_r, "I'm %ld years old", num);
        value = my_snprintf(string, len_buffer, "I'm %ld years old", num);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;

    // 11-й тест. Буфер равен нулю.
    {
        char string[18] = "";
        char string_r[18] = "";
        size_t len_buffer = 0;
        size_t len_buffer_r = 0;
        int value;
        int value_r;
        long int num = 192;
        value_r = snprintf(string_r, len_buffer, "I'm %ld years old", num);
        value = my_snprintf(string, len_buffer_r, "I'm %ld years old", num);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }

    // 12-й тест. Пустая строка.
    {
        char string[18] = "";
        char string_r[18] = "";
        size_t len_buffer = 17;
        size_t len_buffer_r = 17;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer, "a");
        value = my_snprintf(string, len_buffer_r, "a");
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;

    // 13-й тест. Пустая строка.
    {
        char *string = NULL;
        char *string_r = NULL;
        size_t len_buffer = 0;
        size_t len_buffer_r = 0;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer, "Hello");
        value = my_snprintf(string, len_buffer_r, "Hello");
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;

    printf("TEST '%s' - %s\n", __func__, error_count ? "FAIL" : "OK");
}

/*
 * Signed   Unsigned
 * MIN      MAX
 * MAX      0
 * 0        любое отрицательное число
 * -1
 * >MAX
 *
 * String
 * My name is '%s'. I was born in %d.
 * - Буфер достаточной длины
 * - Буфер нулевой длины
 * - Недостаточный буфер
 *      - Недостаточный по %s
 *      - Недостаточный по %d
 * - Пустая строка как параметр
 */
void test_signed(void)
{
    int error_count = 0;
    int i = 1;

    // 1-й тест. Минимальное число (проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer, "%ld", LONG_MIN);
        value = my_snprintf(string, len_buffer_r, "%ld", LONG_MIN);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    // 2-й тест. Максимальное число (проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer, "%ld", LONG_MAX);
        value = my_snprintf(string, len_buffer_r, "%ld", LONG_MAX);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    // 3-й тест. Ноль (проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        long int format = 0;
        value_r = snprintf(string_r, len_buffer, "%ld", format);
        value = my_snprintf(string, len_buffer_r, "%ld", format);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    // 4-й тест. -1 (проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        long int format = -1;
        value_r = snprintf(string_r, len_buffer, "%ld", format);
        value = my_snprintf(string, len_buffer_r, "%ld", format);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;
/*
 * Убрал, тк компилятор выдавал предупреждение о переполнении типа
    // 5-й тест. Число, которое в данном типе не может быть представлено (проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer, "%ld", LONG_MAX + 1);
        value = my_snprintf(string, len_buffer_r, "%ld", LONG_MAX + 1);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;
*/
    printf("TEST '%s' - %s\n", __func__, error_count ? "FAIL" : "OK");
}

void test_unsigned(void)
{
    int error_count = 0;
    int i = 1;

    // 1-й тест. Максимальное число (проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        value_r = snprintf(string_r, len_buffer, "%o", INT_MAX);
        value = my_snprintf(string, len_buffer_r, "%o", INT_MAX);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;

    // 2-й тест. 0 (проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        int format = 0;
        value_r = snprintf(string_r, len_buffer, "%o", format);
        value = my_snprintf(string, len_buffer_r, "%o", format);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;

    // 3-й тест. Отрицательное (Проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        int format = -20;
        value_r = snprintf(string_r, len_buffer, "%o", format);
        value = my_snprintf(string, len_buffer_r, "%o", format);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("Problem with %d-th test", i);
    i++;

    printf("TEST '%s' - %s\n", __func__, error_count ? "FAIL" : "OK");
}

void test_string(void)
{
    int error_count = 0;
    int i = 1;

    // 1-й тест. Буфер достаточной длины (Проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 50;
        size_t len_buffer_r = 50;
        int value;
        int value_r;
        long int year = 19;
        value_r = snprintf(string_r, len_buffer, "My name is '%s'. I was born in %ld.", "Eugen", year);
        value = my_snprintf(string, len_buffer_r, "My name is '%s'. I was born in %ld.", "Eugen", year);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    // 2-й тест. Буфер нулевой длины (Проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 0;
        size_t len_buffer_r = 0;
        int value;
        int value_r;
        long int year = 19;
        value_r = snprintf(string_r, len_buffer, "My name is '%s'. I was born in %ld.", "Eugen", year);
        value = my_snprintf(string, len_buffer_r, "My name is '%s'. I was born in %ld.", "Eugen", year);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    // 3-й тест. Буфер недостаточной длины по %s (Проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 15;
        size_t len_buffer_r = 15;
        int value;
        int value_r;
        long int year = 19;
        value_r = snprintf(string_r, len_buffer, "My name is '%s'. I was born in %ld.", "Eugen", year);
        value = my_snprintf(string, len_buffer_r, "My name is '%s'. I was born in %ld.", "Eugen", year);
        //printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    // 4-й тест. Буфер недостаточной длины по %ld (Проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 37;
        size_t len_buffer_r = 37;
        int value;
        int value_r;
        long int year = -2150;
        value_r = snprintf(string_r, len_buffer, "My name is '%s'. I was born in %ld.", "Eugen", year);
        value = my_snprintf(string, len_buffer_r, "My name is '%s'. I was born in %ld.", "Eugen", year);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    // 5-й тест. Буфер недостаточной длины по %ld (Проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 37;
        size_t len_buffer_r = 37;
        int value;
        int value_r;
        long int year = -2150;
        value_r = snprintf(string_r, len_buffer, "My name is '%s'. I was born in %ld.", "Eugen", year);
        value = my_snprintf(string, len_buffer_r, "My name is '%s'. I was born in %ld.", "Eugen", year);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    // 6-й тест. Пустая строка как параметр (Проходит)
    {
        char string[50] = "";
        char string_r[50] = "";
        size_t len_buffer = 37;
        size_t len_buffer_r = 37;
        int value;
        int value_r;
        long int year = -2150;
        value_r = snprintf(string_r, len_buffer, "My name is '%s'. I was born in %ld.", "", year);
        value = my_snprintf(string, len_buffer_r, "My name is '%s'. I was born in %ld.", "", year);
        // printf("\nsnprintf str: '%s', '%d'\nmy: '%s', '%d'", string_r, value_r, string, value);
        if (my_strcmp(string_r, string) || value != value_r)
            error_count += 1;
    }
    if (error_count)
        printf("\nProblem with %d-th test", i);
    i++;

    printf("TEST '%s' - %s\n", __func__, error_count ? "FAIL" : "OK");
}

int main(void)
{
    test_snprintf();
    test_signed();
    test_unsigned();
    test_string();

    return 0;
}

