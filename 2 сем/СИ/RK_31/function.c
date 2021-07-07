#include "function.h"

void swap_elements(int **matrix, int row, int column)
{
    double tmp;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (j >= i && j <= column - i - 1)
            {
                tmp = matrix[i][j];
                matrix[i][j] = matrix[row - i - 1][j];
                matrix[row - i - 1][j] = tmp;
            }
        }
    }
}

double find_min(int **matrix, int row, int column)
{
    assert(row >= 3 && column >= 3);
    double min = matrix[1][1];
    for (int i = 0; i < row; i++)
    {
        for (int j = i + 1; j < column; j++)
        {
            if (min > matrix[i][j])
            {
                min = matrix[i][j];
            }
        }
    }

    return min;
}

int find_count_of_min(int **matrix, int row, int column, int min)
{
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (matrix[i][j] > min)
                count++;
        }
    }

    return count;
}

void fill_array(int **matrix, int row, int column, int *array, int min)
{
    int k = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (matrix[i][j] > min)
            {
                array[k] = matrix[i][j];
                k++;
            }
        }
    }
}
