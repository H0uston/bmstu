#include "config.h"

bool compare_lists(struct list_t *list_a, struct list_t *list_b)
{
    while (list_a != NULL && list_b != NULL)
    {
        if (!(strcmp(list_a->surname, list_b->surname) == 0 && strcmp(list_a->name, list_b->name) == 0
                && list_a->ent_year == list_b->ent_year && list_a->group == list_b->group))
            return false;

        list_a = list_a->next;
        list_b = list_b->next;
    }

    if (list_a != NULL || list_b != NULL)
        return false;

    return true;
}

void test_my_strstr(void)
{
    int error_count = 0;
    int i = 1;
    // Первый тест. Есть совпадение.
    {
        char str[] = "My name is Evgeniy";
        char substr[] = "geniy";
        if (!(my_strstr(str, substr)))
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Второй тест. Подстрока больше обычной строки
    {
        char str[] = "Hello";
        char substr[] = "HelloM";
        if (my_strstr(str, substr))
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Третий тест. Подстрока больше обычной строки
    {
        char str[] = "Hello";
        char substr[] = "MHello";
        if (my_strstr(str, substr))
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Четвёртый тест. Нет совпадения
    {
        char str[] = "Hello";
        char substr[] = "world";
        if (my_strstr(str, substr))
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Пятый тест. Концы строки не совпадают
    {
        char str[] = "Hello";
        char substr[] = "Hel";
        if (my_strstr(str, substr))
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Шестой тест. Совпадает один символ
    {
        char str[] = "Hello";
        char substr[] = "o";
        if (!(my_strstr(str, substr)))
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Седьмой тест. Совпадает на всю строку
    {
        char str[] = "Programming";
        char substr[] = "Programming";
        if (!(my_strstr(str, substr)))
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    printf("\nTEST '%s' - '%s'", __func__, error_count ? "FAIL" : "OK");
}

void test_sort(void)
{
    int error_count = 0;
    int i = 1;
    // Первый тест. Случайный список
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_1.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_1.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Второй тест. Упорядоченный список (здесь и далее "упорядоченный" - по фамилиям)
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_2.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_2.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Третий тест. Неупорядоченный список
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_3.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_3.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Четвёртый тест. Упорядоченный список из 2-ух элементов
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_4.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_4.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Пятый тест. Неупорядоченный тест из 2-ух элементов
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_5.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_5.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Шестой тест. Список из одного элемента
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_6.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_6.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Седьмой тест. Совпадающие фамилии. Сравнение по именам
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_7.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_7.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Восьмой тест. Совпадающие имена и фамилии
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_8.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_8.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Девятый тест. Упорядоченный список из 3 элементов
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_9.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_9.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    // Десятый тест. Неупорядоченный список из 3-х элементов
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        file_in_a = fopen("tests/test_sort/in_10.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_sort/out_10.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        struct list_t *head = NULL;
        struct list_t *head_right = NULL;
        if (status == OK)
        {
            head = form_list(file_in_a);
            if (!head)
                status = ERR_MEMORY;

            if (status == OK)
            {
                head_right = form_list(file_in_b);
                if (!head_right)
                    status = ERR_MEMORY;
            }
        }

        if (status == OK)
        {
            sort_student(&head);
            if (!(compare_lists(head, head_right)))
                error_count += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (head != NULL)
            free_list_t(head);

        if (head_right != NULL)
            free_list_t(head_right);

        if (status != OK)
            error_count += 1;
    }

    if (error_count)
        printf("\nProblems with %d-th test!", i);
    i += 1;

    printf("\nTEST '%s' - '%s'", __func__, error_count ? "FAIL" : "OK");

}

int main(void)
{
    test_my_strstr();
    test_sort();
    printf("\n");
    return 0;
}

