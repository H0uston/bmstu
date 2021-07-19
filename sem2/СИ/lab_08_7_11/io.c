#include "io.h"

/**
Освобождает память, занятую матрицей.

@param matrix [in] - матрица

*/
void free_matrix(double **matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}

/**
Печатает матрицу в файл.

@param file [in] - файл, куда будет напечатана матрцица
@param matrix [in] - матрица
@param row [in] - количество строк матрицы
@param column [in] - количество столбцов
*/
void io_matrix_fprintf(FILE *file, double **matrix, int row, int column)
{
	int i, j;
    fprintf(file, "%d %d\n", row, column);
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
			fprintf(file, "%lf ", matrix[i][j]);
		fprintf(file, "\n");
	}
}

/**
Выделяет память под матрицу.

@param row [in] - количетсво строк матрицы
@param column [in] - количество столбцов

@return область памяти, выделенную под матрицу.
*/
double **io_allocate_matrix(int row, int column)
{
    double **matrix;
    matrix = malloc(row * sizeof(double *));
    if (!matrix)
        return NULL;

    for (int i = 0; i < row; i++)
    {
        matrix[i] = malloc(column * sizeof(double));
        if (!matrix[i])
        {
            free_matrix(matrix, row);
            return NULL;
        }
    }
    /*
    double **matrix, *data;

    matrix = malloc((row + 1) * sizeof(double*));
    if (!matrix)
        return NULL;

    data = malloc(row * column * sizeof(double));
    if (!data)
    {
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < row; i++)
    {
        matrix[i] = data + i * column;
    }
    matrix[row] = data;
     */

    return matrix;
}

/**
Считывает данные из файла.

@param file [in] - файл, откуда считываются данные
@param matrix [out] - матрица
@param row [in] - количество строк матрицы
@param column [in] - количество столбцов матрицы

@return Возвращает OK, если ошибок не было, либо ERR_DATA, если в файле хранятся ошибочные данные.
*/
int io_read_data(FILE *file, double **matrix, int row, int column)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
        {
            if (fscanf(file, "%lf", &matrix[i][j]) != 1)
                return ERR_DATA;
        }
    return OK;
}

/**
Формирует матрицу из данных определённого файла.

@param name [in] - название файла, откуда будут считаны данные
@param matrix [out] - матрица
@param row [out] - количество строк матрицы
@param column [out] - количество столбцов матрицы

@return Возвращает OK, если ошибок не было, либо ERR_MEMORY, если не удалось выделить память, либо ERR_MATRIX_SIZE, если размеры матрицы некорректны, либо ERR_DATA, если данные в фале ошибочны.
*/
int io_form_matrix(const char *name, double ***matrix, int *row, int *column)
{
    int status = OK;
    FILE *file;
    file = fopen(name, "r");

    if (file == NULL)
        status = ERR_FILE;
    if (status == OK && fscanf(file, "%d %d", row, column) != 2)
        status = ERR_DATA;
    if (status == OK && *row > 0 && *column > 0)
    {
        *matrix = io_allocate_matrix(*row, *column);
        if (*matrix != NULL)
            status = io_read_data(file, *matrix, *row, *column);
        else
            status = ERR_MEMORY;
    }
    else if (status == OK && (*row <= 0 || *column <= 0))
    {
        status = ERR_MATRIX_SIZE;
    }
    if (file != NULL)
        fclose(file);

    return status;
}

/**
Выводит матрицу в определённый файл.

@param name [in] - название файла, куда будут записаны данные
@param matrix [in] - матрица
@param row [in] - количество строк матрицы
@param column [in] - количество столбцов матрицы

@return Возвращает OK, если ошибок не было, либо ERR_FILE, если не удалось открыть файл.
*/
int io_matrix_out(const char *name, double **matrix, int row, int column)
{
    int status = OK;
    FILE *file = fopen(name, "w");
    if (file == NULL)
        status = ERR_FILE;
    if (status == OK)
    {
        io_matrix_fprintf(file, matrix, row, column);
        fclose(file);
    }

    return status;
}

