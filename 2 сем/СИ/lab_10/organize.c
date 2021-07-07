#include "organize.h"

/**
Считывает данные, формирует структуры и производит поиск записи в списке

@param file_name_in[in] - название файла с данными
@param file_name_out[in] - название файла, куда должна быть выведена информация
@param string[in] - название объекта, которого нужно найти в списке

@return OK, если ошибок не было, ERR_MEMORY, если произошла ошибка выделения памяти, или ERR_FILE, если не удалось открыть файл.
*/
int organize_find(const char *file_name_in, const char *file_name_out, const char *string)
{
    int status = OK;
    FILE *file_in = NULL;
    FILE *file_out = NULL;
    file_in = fopen(file_name_in, "r");
    if (!file_in)
        status = ERR_FILE;

    if (status == OK)
    {
        file_out = fopen(file_name_out, "w");
        if (!file_out)
            status = ERR_FILE;
    }

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
        tmp = find(list, (void *)string, compare_string);
        if (tmp != NULL)
            print_planet(file_out, tmp->data);
        else
            printf("Not found\n");
    }

    fclose(file_in);
    fclose(file_out);

    if (list != NULL)
        free_list(list);

    if (data != NULL)
        free_struct(data);

    return status;
}

/**
Считывает данные, формирует структуры и производит удаление последней записи из списка

@param file_name_in[in] - название файла с данными
@param file_name_out[in] - название файла, куда должна быть выведена информация

@return OK, если ошибок не было, ERR_MEMORY, если произошла ошибка выделения памяти, или ERR_FILE, если не удалось открыть файл.
*/
int organize_pop_back(const char *file_name_in, const char *file_name_out)
{
    int status = OK;
    FILE *file_in = NULL;
    FILE *file_out = NULL;
    file_in = fopen(file_name_in, "r");
    if (!file_in)
        status = ERR_FILE;

    if (status == OK)
    {
        file_out = fopen(file_name_out, "w");
        if (!file_out)
            status = ERR_FILE;
    }

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
        struct object *tmp;
        tmp = pop_back(&list);
        if (tmp != NULL)
            print_planet(file_out, tmp);
        else
            printf("Empty list\n");
    }

    fclose(file_in);
    fclose(file_out);

    if (list != NULL)
        free_list(list);

    if (data != NULL)
        free_struct(data);

    return status;
}

/**
Считывает данные, формирует структуры и производит добавление одного списка в другой

@param file_name_in_a[in] - название файла с данными
@param file_name_in_b[in] - название файла с данными
@param file_name_out[in] - название файла, куда должна быть выведена информация

@return OK, если ошибок не было, ERR_MEMORY, если произошла ошибка выделения памяти, или ERR_FILE, если не удалось открыть файл.
*/
int organize_append(const char *file_name_in_a, const char *file_name_in_b, const char *file_name_out)
{
    int status = OK;
    FILE *file_in_a = NULL;
    FILE *file_in_b = NULL;
    FILE *file_out = NULL;
    file_in_a = fopen(file_name_in_a, "r");
    if (!file_in_a)
        status = ERR_FILE;

    if (status == OK)
    {
        file_in_b = fopen(file_name_in_b, "r");
        if (!file_in_b)
            status = ERR_FILE;
    }

    if (status == OK)
    {
        file_out = fopen(file_name_out, "w");
        if (!file_out)
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
        append(&list_a, &list_b);
        print(file_out, list_a);
    }

    fclose(file_in_a);
    fclose(file_in_b);
    fclose(file_out);

    if (list_a != NULL)
        free_list(list_a);

    if (list_b != NULL)
        free_list(list_b);

    if (data_a != NULL)
        free_struct(data_a);

    if (data_b != NULL)
        free_struct(data_b);

    return status;
}

/**
Считывает данные, формирует структуры и производит сортировку списка

@param file_name_in[in] - название файла с данными
@param file_name_out[in] - название файла, куда должна быть выведена информация

@return OK, если ошибок не было, ERR_MEMORY, если произошла ошибка выделения памяти, или ERR_FILE, если не удалось открыть файл.
*/
int organize_sort(const char *file_name_in, const char *file_name_out)
{
    int status = OK;
    FILE *file_in = NULL;
    FILE *file_out = NULL;
    file_in = fopen(file_name_in, "r");
    if (!file_in)
        status = ERR_FILE;

    if (status == OK)
    {
        file_out = fopen(file_name_out, "w");
        if (!file_out)
            status = ERR_FILE;
    }

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
        insertion_sort(&list);
        if (list != NULL)
            print(file_out, list);
    }

    fclose(file_in);
    fclose(file_out);

    if (list != NULL)
        free_list(list);

    if (data != NULL)
        free_struct(data);

    return status;
}

/**
Выводит справку о программе
*/
void organize_info(void)
{
    printf("Справка: Программа для работы со списками, которая реализует поиск элемента в списке,\n"
        "удаление последнего элемента в списке, добавление одного списка в конец другого и сортировку списка.\n"
        "Формат запуска приложения должен быть следующим:\n"
        "app.exe action file_in_1.txt [file_in_2.txt] out_3.txt [string]\n"
        "Возможные значения action:\n"
        "f поиск (для выполнение этой команды нужно добавить string (строку), информацию о которой нужно найти в списке);\n"
        "d возврат значений последнего элемента списка и удаление этого элемента из списка;\n"
        "a добавление в конец списка из file_in_1.txt список из file_in_2.txt (который нужно указать);\n"
        "s сортирует список методом вставок;\n"
        "h выдача справочной информации.\n"
        "Разработчик: Уласик Е.А.\n"
        "Группа: ИУ7-31Б\n");
}