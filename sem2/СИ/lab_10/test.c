//
// Created by Houston on 08/11/2018.
//
#include "config.h"

int compare_lists(node_t *list_a, node_t *list_b)
{
    struct object *tmp_a;
    struct object *tmp_b;
    while (list_a != NULL && list_b != NULL)
    {
        tmp_a = list_a->data;
        tmp_b = list_b->data;

        if (strcmp(tmp_a->name, tmp_b->name) != 0 || fabs(tmp_a->diameter - tmp_b->diameter) > EPS)
            return 1;

        list_a = list_a->next;
        list_b = list_b->next;
    }

    if (list_a != NULL || list_b != NULL)
        return 1;

    return 0;
}

void test_find(void)
{
    int count_error = 0;

    // Тест 1. Элемент есть в списке
    {
        int status = OK;
        FILE *file_in;
        file_in = fopen("tests/test_find/in_1.txt", "r");
        if (!file_in)
            status = ERR_FILE;

        struct object *data = NULL;
        struct node *list = NULL;
        // Изменяется
        double answer_diameter = 6780;

        if (status == OK)
        {
            status = read_from_file(file_in, &data);
            if (status == OK)
                status = form_list(&list, data);
        }

        if (status == OK)
        {
            struct node *tmp;
            // Изменяется
            tmp = find(list, (void *)"Mars", compare_string);
            if (tmp != NULL)
            {
                struct object *p = tmp->data;
                if (fabs(p->diameter - answer_diameter) > EPS)
                    count_error += 1;
            }
            else
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in);

        if (list != NULL)
            free_list(list);

        if (data != NULL)
            free_struct(data);
    }

    // Тест 2. Элемента нет в списке
    {
        int status = OK;
        FILE *file_in;
        file_in = fopen("tests/test_find/in_2.txt", "r");
        if (!file_in)
            status = ERR_FILE;

        struct object *data = NULL;
        struct node *list = NULL;

        if (status == OK)
        {
            status = read_from_file(file_in, &data);
            if (status == OK)
                status = form_list(&list, data);
        }

        if (status == OK)
        {
            struct node *tmp;
            // Изменяется
            tmp = find(list, (void *)"Venus", compare_string);
            if (tmp != NULL)
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in);

        if (list != NULL)
            free_list(list);

        if (data != NULL)
            free_struct(data);
    }

    // Тест 3. Несколько одинаковых элементов. Должен вернуть указатель на первый.
    {
        int status = OK;
        FILE *file_in;
        file_in = fopen("tests/test_find/in_3.txt", "r");
        if (!file_in)
            status = ERR_FILE;

        struct object *data = NULL;
        struct node *list = NULL;
        // Изменяется
        double answer_diameter = 3.12;

        if (status == OK)
        {
            status = read_from_file(file_in, &data);
            if (status == OK)
                status = form_list(&list, data);
        }

        if (status == OK)
        {
            struct node *tmp;
            // Изменяется
            tmp = find(list, (void *)"Comet", compare_string);
            if (tmp != NULL)
            {
                struct object *p = tmp->data;
                if (fabs(p->diameter - answer_diameter) > EPS)
                    count_error += 1;
            }
            else
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in);

        if (list != NULL)
            free_list(list);

        if (data != NULL)
            free_struct(data);
    }

    // Тест 4. Файл пуст
    {
        int status = OK;
        FILE *file_in;
        file_in = fopen("tests/test_find/in_4.txt", "r");
        if (!file_in)
            status = ERR_FILE;

        struct object *data = NULL;
        struct node *list = NULL;

        if (status == OK)
        {
            status = read_from_file(file_in, &data);
            if (status == OK)
                status = form_list(&list, data);
        }

        if (status == OK)
        {
            struct node *tmp;
            // Изменяется
            tmp = find(list, (void *)"Mars", compare_string);
            if (tmp != NULL)
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in);

        if (list != NULL)
            free_list(list);

        if (data != NULL)
            free_struct(data);
    }

    printf("\nTEST '%s' - %s", __func__, count_error ? "FAIL" : "OK");
}

void test_pop_end(void)
{
    int count_error = 0;

    // Тест 1. Обычный список из нескольких элементов.
    {
        int status = OK;
        FILE *file_in;
        file_in = fopen("tests/test_pop_end/in_1.txt", "r");
        if (!file_in)
            status = ERR_FILE;

        struct object *data = NULL;
        struct node *list = NULL;
        // Изменяется
        double answer_diameter = 139822;

        if (status == OK)
        {
            status = read_from_file(file_in, &data);
            if (status == OK)
                status = form_list(&list, data);
        }

        if (status == OK)
        {
            struct object *tmp;
            tmp = pop_back(&list);
            if (tmp != NULL)
            {
                if (compare_string(tmp, (void *)"Jupiter") != 0 || fabs(tmp->diameter - answer_diameter) > EPS)
                    count_error += 1;
            }
            else
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in);

        if (list != NULL)
            free_list(list);

        if (data != NULL)
            free_struct(data);
    }

    // Тест 2. Список из одного элемента
    {
        int status = OK;
        FILE *file_in;
        file_in = fopen("tests/test_pop_end/in_2.txt", "r");
        if (!file_in)
            status = ERR_FILE;

        struct object *data = NULL;
        struct node *list = NULL;
        // Изменяется
        double answer_diameter = 12103.6;

        if (status == OK)
        {
            status = read_from_file(file_in, &data);
            if (status == OK)
                status = form_list(&list, data);
        }

        if (status == OK)
        {
            struct object *tmp;
            tmp = pop_back(&list);
            if (tmp != NULL)
            {
                if (compare_string(tmp, (void *)"Venus") != 0 || fabs(tmp->diameter - answer_diameter) > EPS)
                    count_error += 1;
            }
            else
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in);

        if (list != NULL)
            free_list(list);

        if (data != NULL)
            free_struct(data);
    }

    // Тест 3. Список пуст
    {
        struct node *list = NULL;

        struct object *tmp;
        tmp = pop_back(&list);
        if (tmp != NULL)
            count_error += 1;

        if (list != NULL)
            free_list(list);
    }

    printf("\nTEST '%s' - %s", __func__, count_error ? "FAIL" : "OK");
}

void test_append(void)
{
    int count_error = 0;

    // Тест 1. Объединение двух списков
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_b = NULL;
        FILE *file_in_c = NULL;

        file_in_a = fopen("tests/test_append/in_1_a.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_append/in_1_b.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        if (status == OK)
        {
            file_in_c = fopen("tests/test_append/out_1.txt", "r");
            if (!file_in_c)
                status = ERR_FILE;
        }

        struct object *data_a = NULL;
        struct node *list_a = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_a, &data_a);
            if (status == OK)
                status = form_list(&list_a, data_a);
        }

        struct object *data_b = NULL;
        struct node *list_b = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_b, &data_b);
            if (status == OK)
                status = form_list(&list_b, data_b);
        }

        struct object *data_c = NULL;
        struct node *list_c = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_c, &data_c);
            if (status == OK)
                status = form_list(&list_c, data_c);
        }

        if (status == OK)
        {
            append(&list_a, &list_b);
            if (compare_lists(list_a, list_c) != 0)
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in_a);
        fclose(file_in_b);
        fclose(file_in_c);

        if (list_a != NULL)
            free_list(list_a);

        if (list_b != NULL)
            free_list(list_b);

        if (list_c != NULL)
            free_list(list_c);

        if (data_a != NULL)
            free_struct(data_a);

        if (data_b != NULL)
            free_struct(data_b);

        if (data_c != NULL)
            free_struct(data_c);
    }

    // Тест 2. Объединение двух списков. Второй список пуст.
    {
        int status = OK;
        FILE *file_in_a = NULL;
        FILE *file_in_c = NULL;

        file_in_a = fopen("tests/test_append/in_2.txt", "r");
        if (!file_in_a)
            status = ERR_FILE;

        if (status == OK)
        {
            file_in_c = fopen("tests/test_append/out_2.txt", "r");
            if (!file_in_c)
                status = ERR_FILE;
        }

        struct object *data_a = NULL;
        struct node *list_a = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_a, &data_a);
            if (status == OK)
                status = form_list(&list_a, data_a);
        }

        struct node *list_b = NULL;

        struct object *data_c = NULL;
        struct node *list_c = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_c, &data_c);
            if (status == OK)
                status = form_list(&list_c, data_c);
        }

        if (status == OK)
        {
            append(&list_a, &list_b);
            if (compare_lists(list_a, list_c) != 0)
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in_a);
        fclose(file_in_c);

        if (list_a != NULL)
            free_list(list_a);

        if (list_b != NULL)
            free_list(list_b);

        if (list_c != NULL)
            free_list(list_c);

        if (data_a != NULL)
            free_struct(data_a);

        if (data_c != NULL)
            free_struct(data_c);
    }

    // Тест 3. Объединение двух списков. Первый список пуст
    {
        int status = OK;
        FILE *file_in_b = NULL;
        FILE *file_in_c = NULL;

        if (status == OK)
        {
            file_in_b = fopen("tests/test_append/in_3.txt", "r");
            if (!file_in_b)
                status = ERR_FILE;
        }

        if (status == OK)
        {
            file_in_c = fopen("tests/test_append/out_3.txt", "r");
            if (!file_in_c)
                status = ERR_FILE;
        }

        struct node *list_a = NULL;

        struct object *data_b = NULL;
        struct node *list_b = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_b, &data_b);
            if (status == OK)
                status = form_list(&list_b, data_b);
        }

        struct object *data_c = NULL;
        struct node *list_c = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_c, &data_c);
            if (status == OK)
                status = form_list(&list_c, data_c);
        }

        if (status == OK)
        {
            append(&list_a, &list_b);
            if (compare_lists(list_a, list_c) != 0)
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in_b);
        fclose(file_in_c);

        if (list_a != NULL)
            free_list(list_a);

        if (list_b != NULL)
            free_list(list_b);

        if (list_c != NULL)
            free_list(list_c);

        if (data_b != NULL)
            free_struct(data_b);

        if (data_c != NULL)
            free_struct(data_c);
    }

    printf("\nTEST '%s' - %s", __func__, count_error ? "FAIL" : "OK");
}

void test_sort(void)
{
    int count_error = 0;

    // Тест 1. Сортировка случайного списка
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

        struct object *data_a = NULL;
        struct node *list_a = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_a, &data_a);
            if (status == OK)
                status = form_list(&list_a, data_a);
        }

        struct object *data_b = NULL;
        struct node *list_b = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_b, &data_b);
            if (status == OK)
                status = form_list(&list_b, data_b);
        }

        if (status == OK)
        {
            insertion_sort(&list_a);
            if (compare_lists(list_a, list_b) != 0)
                count_error += 1;
        }
        else
            count_error += 1;

        fclose(file_in_a);
        fclose(file_in_b);

        if (list_a != NULL)
            free_list(list_a);

        if (data_a != NULL)
            free_struct(data_a);

        if (list_b != NULL)
            free_list(list_b);

        if (data_b != NULL)
            free_struct(data_b);
    }

    // Тест 2. Упорядоченный список
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

        struct object *data_a = NULL;
        struct node *list_a = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_a, &data_a);
            if (status == OK)
                status = form_list(&list_a, data_a);
        }

        struct object *data_b = NULL;
        struct node *list_b = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_b, &data_b);
            if (status == OK)
                status = form_list(&list_b, data_b);
        }

        if (status == OK)
        {
            insertion_sort(&list_a);
            if (compare_lists(list_a, list_b) != 0)
                count_error += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (list_a != NULL)
            free_list(list_a);

        if (data_a != NULL)
            free_struct(data_a);

        if (list_b != NULL)
            free_list(list_b);

        if (data_b != NULL)
            free_struct(data_b);
    }

    // Тест 3. Обратный список
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

        struct object *data_a = NULL;
        struct node *list_a = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_a, &data_a);
            if (status == OK)
                status = form_list(&list_a, data_a);
        }

        struct object *data_b = NULL;
        struct node *list_b = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_b, &data_b);
            if (status == OK)
                status = form_list(&list_b, data_b);
        }

        if (status == OK)
        {
            insertion_sort(&list_a);
            if (compare_lists(list_a, list_b) != 0)
                count_error += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (list_a != NULL)
            free_list(list_a);

        if (data_a != NULL)
            free_struct(data_a);

        if (list_b != NULL)
            free_list(list_b);

        if (data_b != NULL)
            free_struct(data_b);
    }

    // Тест 4. Упорядоченный список из 2 элементов
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

        struct object *data_a = NULL;
        struct node *list_a = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_a, &data_a);
            if (status == OK)
                status = form_list(&list_a, data_a);
        }

        struct object *data_b = NULL;
        struct node *list_b = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_b, &data_b);
            if (status == OK)
                status = form_list(&list_b, data_b);
        }

        if (status == OK)
        {
            insertion_sort(&list_a);
            if (compare_lists(list_a, list_b) != 0)
                count_error += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (list_a != NULL)
            free_list(list_a);

        if (data_a != NULL)
            free_struct(data_a);

        if (list_b != NULL)
            free_list(list_b);

        if (data_b != NULL)
            free_struct(data_b);
    }

    // Тест 5. Неупорядоченный список из 2 элементов
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

        struct object *data_a = NULL;
        struct node *list_a = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_a, &data_a);
            if (status == OK)
                status = form_list(&list_a, data_a);
        }

        struct object *data_b = NULL;
        struct node *list_b = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_b, &data_b);
            if (status == OK)
                status = form_list(&list_b, data_b);
        }

        if (status == OK)
        {
            insertion_sort(&list_a);
            if (compare_lists(list_a, list_b) != 0)
                count_error += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (list_a != NULL)
            free_list(list_a);

        if (data_a != NULL)
            free_struct(data_a);

        if (list_b != NULL)
            free_list(list_b);

        if (data_b != NULL)
            free_struct(data_b);
    }

    // Тест 6. Список из одного элемента
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

        struct object *data_a = NULL;
        struct node *list_a = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_a, &data_a);
            if (status == OK)
                status = form_list(&list_a, data_a);
        }

        struct object *data_b = NULL;
        struct node *list_b = NULL;
        if (status == OK)
        {
            status = read_from_file(file_in_b, &data_b);
            if (status == OK)
                status = form_list(&list_b, data_b);
        }

        if (status == OK)
        {
            insertion_sort(&list_a);
            if (compare_lists(list_a, list_b) != 0)
                count_error += 1;
        }

        fclose(file_in_a);
        fclose(file_in_b);

        if (list_a != NULL)
            free_list(list_a);

        if (data_a != NULL)
            free_struct(data_a);

        if (list_b != NULL)
            free_list(list_b);

        if (data_b != NULL)
            free_struct(data_b);
    }

    printf("\nTEST '%s' - %s\n", __func__, count_error ? "FAIL" : "OK");
}

int main(void)
{
    test_find();
    test_pop_end();
    test_append();
    test_sort();

    return 0;
}
