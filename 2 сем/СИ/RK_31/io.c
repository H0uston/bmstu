#include "io.h"

int **allocate_matrix(int row, int column)
{
    int **matrix = calloc(row, sizeof(int *));
    if (!matrix)
        return NULL;

    for (int i = 0; i < row; i++)
    {
        matrix[i] = malloc(column * sizeof(int));
        if (!matrix[i])
        {
            free_matrix(matrix, row);
            return NULL;
        }
    }

    return matrix;
}

int read_data(char *file_name, int ***matrix, int *row, int *column)
{
    int status = OK;
    FILE *file = fopen(file_name, "r");
    if (!file)
        return ERR_FILE;

    if (fscanf(file, "%d %d", row, column) == 2)
    {
        *matrix = allocate_matrix(*row, *column);
        if (!matrix)
            return ERR_MEMORY;

        double num;
        for (int i = 0; i < *row; i++)
        {
            for (int j = 0; j < *column; j++)
            {
                if (fscanf(file, "%lf", &num) == 1)
                    (*matrix)[i][j] = num;
            }
        }
    }
    else
    {
        status = ERR_DATA;
    }

    return status;
}

void matrix_printf(int **matrix, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void array_printf(int *array, int count)
{
    printf("\n");
    for (int i = 0; i < count; i++)
        printf("%d ", array[i]);
}

void free_matrix(int **matrix, int row)
{
    for (int i = 0; i < row; i++)
        free(matrix[i]);

    free(matrix);
}
