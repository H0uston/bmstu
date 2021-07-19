#include <string.h>
#include "function.h"
#include "my_string.h"

void test_len(void)
{
    int error_count = 0;

    // Первый тест. Обычная строка.
    {
        char str[] = "My name is Johnny";
        size_t str_size = len(str);
        size_t str_size_right = strlen(str);

        if (str_size != str_size_right)
            error_count += 1;
    }

    // Второй тест. Пустая строка.
    {
        char str[] = "";
        size_t str_size = len(str);
        size_t str_size_right = strlen(str);

        if (str_size != str_size_right)
            error_count += 1;
    }

    // Третий тест. Строка из пробелом из спец. символов.
    {
        char str[] = " \n\n!@$?.\\";
        size_t str_size = len(str);
        size_t str_size_right = strlen(str);

        if (str_size != str_size_right)
            error_count += 1;
    }

    printf("TEST '%s' - %s\n", __func__, error_count ? "FAILED" : "PASSED");
}

void test_getline(void)
{
    int error_count = 0;

    // Первый тест. Файл с одним символом.
    {
        FILE *file = fopen("tests/getline/in_2.txt", "r");
        if (file == NULL)
        {
            printf("Can't find directory with test's files.");
            exit(ERR_FILE);
        }
        size_t size_buffer = 128;
        char *result = NULL;

        my_getline(&result, &size_buffer, file);

        char result_right[] = "B";

        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result);
        fclose(file);
    }

    // Второй тест. Файл со строкой.
    {
        FILE *file = fopen("tests/getline/in_3.txt", "r");
        if (file == NULL)
        {
            printf("Can't find directory with test's files.");
            exit(ERR_FILE);
        }
        size_t size_buffer = 128;
        char *result = NULL;

        my_getline(&result, &size_buffer, file);

        char result_right[] = "It's a beautiful life.";

        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result);

        fclose(file);
    }

    // Третий тест. Строка с переходом на следующую строку.
    {
        FILE *file = fopen("tests/getline/in_4.txt", "r");
        if (file == NULL)
        {
            printf("Can't find directory with test's files.");
            exit(ERR_FILE);
        }
        size_t size_buffer = 128;
        char *result = NULL;

        my_getline(&result, &size_buffer, file);

        char result_right[] = "Pod dogd' kosoi s kosoi kosoi po kosoi za kosoi kosoi kosoi kosoi kosoi kosoi kosil travu.\n";

        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result);

        fclose(file);
    }

    printf("TEST '%s' - %s\n", __func__, error_count ? "FAILED" : "PASSED");
}

void test_replace(void)
{
    int error_count = 0;

    // Первый тест. Полная замена строки.
    {
        char source[] = "aaaaaa";
        char search[] = "aaa";
        char replace[] = "bb";
        char *result = str_replace(source, search, replace);
        char result_right[] = "bbbb";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result);
    }

    // Второй тест. Заменяемая строка больше искомой.
    {
        char source[] = "Hallo, meine Freunden!";
        char search[] = "Hallo";
        char replace[] = "Guten Abend";
        char *result = str_replace(source, search, replace);
        char result_right[] = "Guten Abend, meine Freunden!";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result);
    }

    // Третий тест. После замены осталась пустая строка.
    {
        char source[] = "lololololo";
        char search[] = "lo";
        char replace[] = "";
        char *result = str_replace(source, search, replace);
        char result_right[] = "";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result);
    }

    // Четвёртый тест. Несколько замен.
    {
        char source[] = "Today was very bad day.";
        char search[] = "d";
        char replace[] = "n";
        char *result = str_replace(source, search, replace);
        char result_right[] = "Tonay was very ban nay.";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result);
    }

    // Пятый тест.
    {
        char source[] = "help help help help help help death help help death fear";
        char search[] = "help";
        char replace[] = "OK";
        char *result = str_replace(source, search, replace);
        char result_right[] = "OK OK OK OK OK OK death OK OK death fear";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result);
    }

    // 6th test. Source and search lines are space.
    {
        char source[] = " ";
        char search[] = " ";
        char replace[] = "help";
        char *result = str_replace(source, search, replace);
        char result_right[] = "help";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result); 
    }

    // 7th test. Source and search lines are empty.
    {
        char source[] = "";
        char search[] = "";
        char replace[] = "help";
        char *result = str_replace(source, search, replace);
        char result_right[] = "";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result); 
    }

    // 8th test. All lines are empty.
    {
        char source[] = "";
        char search[] = "";
        char replace[] = "";
        char *result = str_replace(source, search, replace);
        char result_right[] = "";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result); 
    }

    // 9th test. Only source line is empty.
    {
        char source[] = "";
        char search[] = "help";
        char replace[] = "fear";
        char *result = str_replace(source, search, replace);
        char result_right[] = "";
        if (!str_compare(result, result_right))
            error_count += 1;

        if (result != NULL)
            free(result); 
    } 
    printf("TEST '%s' - %s\n", __func__, error_count ? "FAILED" : "PASSED");
}

int main(void)
{
    test_len();
    test_getline();
    test_replace();

    return 0;
}

