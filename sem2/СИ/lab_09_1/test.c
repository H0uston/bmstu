//
// Created by Евгений on 14.10.2018.
//
#include "function.h"

int compare_str(char *str_a, char *str_b, int size)
{
    for (int i = 0; i < size; i++)
        if (str_a[i] != str_b[i])
            return FAIL;
    return OK;
}

void test_my_strrchr(void)
{
    int error_count = 0;
    // Первый тест. Первый символ.
    {
        char str[] = "hello";
        char *pointer = my_strrchr(str, 'h');
        char *pointer_right = strrchr(str, 'h');
        if (pointer != pointer_right)
            error_count += 1;
    }
    // Второй тест. Функция должна найти именно последний символ.
    {
        char str[] = "Deep dark fantasies";
        char *pointer = my_strrchr(str, 'a');
        char *pointer_right = strrchr(str, 'a');
        if (pointer != pointer_right)
            error_count += 1;
    }
    // Третий тест. Символ окончания строки.
    {
        char str[] = "TAKE IT BOIIII";
        char *pointer = my_strrchr(str, '\0');
        char *pointer_right = strrchr(str, '\0');
        if (pointer != pointer_right)
            error_count += 1;
    }
    // Четвертый тест. Символа нет в строке.
    {
        char str[] = "C - my favourite language";
        char *pointer = my_strrchr(str, 'z');
        char *pointer_right = strrchr(str, 'z');
        if (pointer != pointer_right)
            error_count += 1;
    }
    printf("TEST %s : %s", __func__, error_count ? "FAIL" : "OK");
}

void test_my_strdup(void)
{
    int error_count = 0;
    // Первый тест. Обычная строка.
    {
        char str[11] = "0123456789";

        char *my_str, *right_str;

        my_str = my_strdup(str);
        right_str = strdup(str);
        if (strlen(my_str) == strlen(right_str))
        {
            if (compare_str(my_str, right_str, strlen(my_str)))
                error_count += 1;
        }
        else
            error_count += 1;

        free(my_str);
        free(right_str);
    }
    // Второй тест. Пустая строка.
    {
        char str[1] = "";

        char *my_str, *right_str;

        my_str = my_strdup(str);
        right_str = strdup(str);
        if (strlen(my_str) == strlen(right_str))
        {
            if (compare_str(my_str, right_str, strlen(my_str)))
                error_count += 1;
        }
        else
            error_count += 1;

        free(my_str);
        free(right_str);
    }
    // Третий тест. Строка из пробелов.
    {
        char str[5] = "    ";

        char *my_str, *right_str;

        my_str = my_strdup(str);
        right_str = strdup(str);
        if (strlen(my_str) == strlen(right_str))
        {
            if (compare_str(my_str, right_str, strlen(my_str)))
                error_count += 1;
        }
        else
            error_count += 1;

        free(my_str);
        free(right_str);
    }
    // Четвертый тест. Обычная строка.
    {
        char str[13] = "hello, world";

        char *my_str, *right_str;

        my_str = my_strdup(str);
        right_str = strdup(str);
        if (strlen(my_str) == strlen(right_str))
        {
            if (compare_str(my_str, right_str, strlen(my_str)))
                error_count += 1;
        }
        else
            error_count += 1;

        free(my_str);
        free(right_str);
    }
    // Пятый тест. Строка кириллицы.
    {
        char str[15] = "Свобода";

        char *my_str, *right_str;

        my_str = my_strdup(str);
        right_str = strdup(str);
        if (strlen(my_str) == strlen(right_str))
        {
            if (compare_str(my_str, right_str, strlen(my_str)))
                error_count += 1;
        }
        else
            error_count += 1;

        free(my_str);
        free(right_str);
    }
    printf("\nTEST %s : %s", __func__, error_count ? "FAIL" : "OK");
}

int main(void)
{
    test_my_strrchr();
    test_my_strdup();

    return 0;
}
