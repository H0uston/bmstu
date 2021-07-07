#include "organize.h"

/**
Производит все проверки для суммы матриц.

@param file_name_a [in] - название файла с матрицей
@param file_name_b [in] - название файла с матрицей
@param file_name_c [in] - название файла, куда будет выведена матрица с результатом

@return Возвращает OK, если ошибок не было, либо ERR_MEMORY, если не удалось выделить память, либо ERR_MATRIX, если размеы матрицы некорректны, либо ERR_FILE, если не удалось открыть файл.
*/
int organize_sum(const char *file_name_a, const char *file_name_b, const char *file_name_c)
{
	int status = OK;
	double **matrix_a = NULL;
	int row_a, column_a;
	double **matrix_b = NULL;
	int row_b, column_b;

	status = io_form_matrix(file_name_a, &matrix_a, &row_a, &column_a);

	if (status == OK)
		status = io_form_matrix(file_name_b, &matrix_b, &row_b, &column_b);

	if (status == OK && row_a == row_b && column_a == column_b)
	{
		double **matrix_c = io_allocate_matrix(row_a, column_a);
		if (matrix_c != NULL)
		{
			sum(matrix_a, matrix_b, matrix_c, row_a, column_a);
			status = io_matrix_out(file_name_c, matrix_c, row_a, column_a);
		}

		if (matrix_c != NULL)
			free_matrix(matrix_c, row_a);
	}
	else if (status == OK && (row_a != row_b || column_a != column_b))
		status = ERR_MATRIX_SIZE;

	if (matrix_a != NULL)
		free_matrix(matrix_a, row_a);
	if (matrix_b != NULL)
		free_matrix(matrix_b, row_b);

	return status;
}

/**
Производит все проверки для умножения матриц.

@param file_name_a [in] - название файла с матрицей
@param file_name_b [in] - название файла с матрицей
@param file_name_c [in] - название файла, куда будет выведена матрица с результатом

@return Возвращает OK, если ошибок не было, либо ERR_MEMORY, если не удалось выделить память, либо ERR_MATRIX, если размеы матрицы некорректны, либо ERR_FILE, если не удалось открыть файл.
*/
int organize_mult(const char *file_name_a, const char *file_name_b, const char *file_name_c)
{
	int status = OK;
	double **matrix_a = NULL;
	int row_a, column_a;
	double **matrix_b = NULL;
	int row_b, column_b;

	status = io_form_matrix(file_name_a, &matrix_a, &row_a, &column_a);

	if (status == OK)
		status = io_form_matrix(file_name_b, &matrix_b, &row_b, &column_b);

	if (status == OK)
	{
		if (row_a == column_b)
		{
			double **matrix_c = io_allocate_matrix(row_a, column_b);
			if (matrix_c != NULL)
			{
				mult(matrix_a, matrix_b, matrix_c, row_a, column_b, column_a);
				status = io_matrix_out(file_name_c, matrix_c, row_a, column_b);
			}

			if (matrix_c != NULL)
				free_matrix(matrix_c, row_a);
		}
		else if (column_a == row_b)
		{
			double **matrix_c = io_allocate_matrix(row_a, column_b);
			if (matrix_c != NULL)
			{
				mult(matrix_a, matrix_b, matrix_c, row_a, column_b, column_a);
				status = io_matrix_out(file_name_c, matrix_c, row_a, column_b);
			}

			if (matrix_c != NULL)
				free_matrix(matrix_c, row_a);
		}
		else 
			status = ERR_MATRIX_SIZE;
	}

	if (matrix_a != NULL)
		free_matrix(matrix_a, row_a);
	if (matrix_b != NULL)
		free_matrix(matrix_b, row_b);

	return status;
}

/**
Производит обращение матрицы методом элементарных преобразований.

@param file_name_a [in] - название файла с матрицей
@param file_name_b [in] - название файла, куда будет выведена матрица с результатом

@return Возвращает OK, если ошибок не было, либо ERR_MEMORY, если не удалось выделить память, либо ERR_MATRIX, если размеы матрицы некорректны, либо ERR_FILE, если не удалось открыть файл.
*/
int organize_invertible(const char *file_name_a, const char *file_name_b)
{
	int status = OK;
	double **matrix = NULL;
	int row, column;

	status = io_form_matrix(file_name_a, &matrix, &row, &column);

	if (status == OK && row == column)
	{
		double determinant;
		status = func_determinant(matrix, &determinant, row);
		if (status == OK)
		{
			if (fabs(0 - determinant) < EPS)
				status = ERR_DETER;
			else
			{
				double **matrix_e = NULL;
				status = form_matrix_e(&matrix_e, row);
				if (status == OK)
				{
					inverse(matrix, &matrix_e, row);
					status = io_matrix_out(file_name_b, matrix_e, row, row);
				}

				if (matrix_e != NULL)
					free_matrix(matrix_e, row);
			}
		}
	}
	else
	    status = ERR_MATRIX_SIZE;

	if (matrix != NULL)
		free_matrix(matrix, row);

	return status;
}

/**
Выводит справку по программе.
*/
void organize_info(void)
{
	printf("Справка: Программа для работы с матрицами, которая реализует сложение матриц,\n"
        "умножение матриц и вычисление обратной матрицы методом элементарных преобразований.\n"
        "Формат запуска приложения должен быть следующим:\n"
        "app.exe action mtr_1.txt [mtr_2.txt] res.txt\n"
        "Возможные значения action:\n"
        "a сложение;\n"
        "m умножение;\n"
        "o вычисление обратной матрицы методом элементарных "
        "преобразований (для нее mtr_2.txt не указывается);\n"
        "h выдача справочной информации.\n"
        "Разработчик: Уласик Е.А.\n"
        "Группа: ИУ7-31Б\n");
}
