#include "config.h"

int main(int args, char **argv)
{
    int status = OK;
    if (args != 2)
        status = ERR_CMD;

    FILE *file;
    if (status == OK)
    {
        file = fopen(argv[1], "r");
        if (file == NULL)
            status = ERR_FILE;
    }

    char *char_result;
    size_t size_result = 0;
    size_t count_row = 0;
    if (status == OK)
    {
        // Считывает из файла строки
        status = read_data(file, &char_result, &size_result, &count_row);
        // printf("\nString: '%s'\nSize: %d\nCount_row: %d\n", char_result, (int)size_result, (int)count_row);
    }

    //size_t count_column = 0;
    // Вычисляем число столбцов
    // Не успел реализовать
    //if (status == OK)
    //{
    //    status = find_count_column(char_result, count_row, &count_column);
    //    printf("Count column: %d", count_column);
    //}
    // Выделяем память для матрицы

    // Из массива char элементы переносим в матрицу int

    // Печатаем матрицу int

    if (char_result != NULL)
        free(char_result);

    if (status == OK)
        printf("Program was completed.");
    else if (status == ERR_FILE)
        printf("Problems with file");
    else if (status == ERR_CMD)
        printf("Wrong CMD! app.exe file_name.txt");
    else
        printf("Unknown error!");

    return status;
}
