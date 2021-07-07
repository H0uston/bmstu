#include "config.h"

int main(int args, char **argv)
{
    if (args != 3)
    {
        printf("Wrong CMD! app.exe file_name.txt s/f\n");
        return ERR_CMD;
    }

    int row, column;
    int **matrix = NULL;
    int status = OK;

    status = read_data(argv[1], &matrix, &row, &column);

    if (status == OK && strcmp(argv[2], "s") == 0)
    {
        printf("\nMatrix before being proccessed:\n");
        matrix_printf(matrix, row, column);
        swap_elements(matrix, row, column);
        printf("\nMatrix after being proccessed:\n");
        matrix_printf(matrix, row, column);
        free_matrix(matrix, row);
    }
    else if (status == OK && strcmp(argv[2], "f") == 0)
    {
        if (row < 3 || column < 3)
            status = ERR_SIZE;
        else
        {
            printf("\nMatrix before being proccessed:\n");
            matrix_printf(matrix, row, column);
            int min = find_min(matrix, row, column);
            int count = find_count_of_min(matrix, row, column, min);
            if (count > 0)
            {
                int *array = malloc(count * sizeof(int));
                if (!array)
                    return ERR_MEMORY;
                fill_array(matrix, row, column, array, min);
                array_printf(array, count);
                free(array);
                free_matrix(matrix, row);
            }
            else
            {
                printf("\nThere are no elements in array");
            }
        }

    }
    if (status != OK)
    {
        if (status == ERR_MEMORY)
            printf("\nProblems with memory!");
        else if (status == ERR_FILE)
            printf("\nProblems with file!");
        else if (status == ERR_DATA)
            printf("\nProblems with data!");
        else if (status == ERR_SIZE)
            printf("\nMatrix is too small for being proccessed.");
        else
            printf("Unknown error!");
    }

    return status;
}
