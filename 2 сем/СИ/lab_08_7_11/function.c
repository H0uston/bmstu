#include "function.h"
/**
Производит сложение двух матриц в третью.

@param matrix_a [in] - матрица
@param matrix_b [in] - матрица
@param matrix_c [out] - матрица, c суммой элементов двух других матриц
@param row [in] - количество строк матриц
@param column [in] - количество столбцов матриц

*/
void sum(double **matrix_a, double **matrix_b, double **matrix_c, int row, int column)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			matrix_c[i][j] = matrix_a[i][j] + matrix_b[i][j];
}

/**
Производит умножение двух матриц в третью.

@param matrix_a [in] - матрица
@param matrix_b [in] - матрица
@param matrix_c [out] - матрица, c произведением элементов двух других матриц
@param max_i [in] - количество строк matrix_c
@param max_j [in] - количество столбцов matrix_c
@param max_k [in] - количество строк matrix_a

*/
void mult(double **matrix_a, double **matrix_b, double **matrix_c, int max_i, int max_j, int max_k)
{
	int j, k;
	double sum;
	for (int i = 0; i < max_i; i++)
		for (j = 0; j < max_j; j++)
		{
		    sum = 0;
			for (k = 0; k < max_k; k++)
			{
				sum += matrix_a[i][k] * matrix_b[k][j];
			}
			matrix_c[i][j] = sum;
		}
}

/**
Производит минора матрицы.

@param matrix [out] - матрица
@param temp [in] - матрица
@param row [in] - количество строк матрицы
@param column [in] - количество столбцов матрицы
@param size [in] - размеры матрицы

*/
void find_minor(double **matrix, double **temp, int row, int column, int size)
{ 
    int temp_i = 0, temp_j = 0; 
  
    for (int i = 0; i < size; i++) 
    { 
        for (int j = 0; j < size; j++) 
        { 
            if (i != row && j != column) 
            { 
                temp[temp_i][temp_j] = matrix[i][j];
                temp_j++;
                if (temp_j == size - 1) 
                { 
                    temp_j = 0; 
                    temp_i++; 
                } 
            } 
        } 
    } 
}

/**
Производит вычисление определителя матрицы.

@param matrix [in] - матрица
@param result [out] - детерминант
@param size [in] - размеры матрицы

@return Возвращает OK, если ошибок не было, либо ERR_MEMORY, если не удалось выделить память.
*/
int func_determinant(double **matrix, double *result, int size)
{
    int status = OK;
    double determinant = 0;

    if (size == 1)
    {
        *result = matrix[0][0];
        return OK;
    }

    double **temp = io_allocate_matrix(size - 1, size - 1);
    if (temp == NULL)
        status = ERR_MEMORY;
    else
    {
        int sign = 1;
        for (int i = 0; i < size; i++)
        {
            // Calculation of the determinant by the first row
            find_minor(matrix, temp, 0, i, size);
            double minor_determinant;
            status = func_determinant(temp, &minor_determinant, size - 1);
            if (status != OK)
                break;
            determinant += sign * matrix[0][i] * minor_determinant;
            sign *= -1;
        }
    }
    if (temp != NULL)
        free_matrix(temp, size - 1);

    if (status == OK)
        *result = determinant;
    return OK;
}

/**
Производит поиск главного элемента матрицы.

@param matrix [in/out] - матрица
@param matrix_e [in/out] - единичная матрица
@param size [in] - размеры матрицы
*/
void find_main_element(double **matrix, double **matrix_e, int column, int size)
{
    assert(size > 0);
    double max = matrix[column][column];
    int max_i = column;
    for (int i = column + 1; i < size; i++)
    {
        // printf("\n%lf\n", matrix[i][column]);
        if (matrix[i][column] > max)
        {
            max = matrix[i][column];
            max_i = i;
        }
    }

    if (max_i != column)
    {
        double *tmp;

        tmp = matrix[column];
        matrix[column] = matrix[max_i];
        matrix[max_i] = tmp;

        tmp = matrix_e[column];
        matrix_e[column] = matrix_e[max_i];
        matrix_e[max_i] = tmp;

        /*
        for (int i = 0; i < size; i++)
        {
            tmp = matrix[column][i];
            matrix[column][i] = matrix[max_i][i];
            matrix[max_i][i] = tmp;
        }

        for (int i = 0; i < size; i++)
        {
            tmp = matrix_e[column][i];
            matrix_e[column][i] = matrix_e[max_i][i];
            matrix_e[max_i][i] = tmp;
        }
        */
    }
}

/**
Производит обращение матрицы.

@param matrix [in] - матрица
@param matrix_e [in/out] - единичная матрица
@param size [in] - размеры матрицы

*/
void inverse(double **matrix, double ***matrix_e, int size)
{
    int i, j, k, z;
    double koef, res;
    // Приведение матрицы к ступенчатому виду
    for (i = 0; i < size; i++)
    {
        // Находим главный элемент
        find_main_element(matrix, *matrix_e, i, size);
        koef = 1 / matrix[i][i];
        // Делим всю строку на элемент первой строки
        for (j = 0; j < size; j++)
        {
            matrix[i][j] *= koef;
            (*matrix_e)[i][j] *= koef;
        }
        // Приводим элементы под главной диагональю к нулю
        for (k = i + 1; k < size; k++)
        {
            res = matrix[k][i];
            for (z = 0; z < size; z++)
            {
                matrix[k][z] -= matrix[i][z] * res;
                (*matrix_e)[k][z] -= (*matrix_e)[i][z] * res;
            }
        }
    }
    // Приводим к нулю элементы над главной диагональю
    for (i = size - 1; i >= 0; i--)
    {
        for (j = i - 1; j >= 0; j--)
        {
            res = matrix[j][i];
            for (k = size - 1; k >= 0; k--)
            {
                matrix[j][k] = matrix[j][k] - matrix[i][k] * res;
                (*matrix_e)[j][k] = (*matrix_e)[j][k] - (*matrix_e)[i][k] * res;
            }
        }
    }
}

/**
Производит формирование единичной матрицы.

@param matrix [out] - единичная матрица
@param size [in] - размеры матрицы

@return Возвращает OK, если ошибок не было, либо ERR_MEMORY, если не удалось выделить память.
*/
int form_matrix_e(double ***matrix_e, int size)
{
    int status = OK;
    int i, j;

    *matrix_e = io_allocate_matrix(size, size);

    if (*matrix_e == NULL)
        status = ERR_MEMORY;

    if (status == OK)
    {
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
            {
                (*matrix_e)[i][j] = 0.0;

                if (i == j)
                    (*matrix_e)[i][j] = 1.0;
            }
    }

    return status;
}
