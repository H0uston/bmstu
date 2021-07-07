#include <stdio.h>
#include <math.h>

#define FAIL -1
#include "function.h"
#include "io.h"
#define EPS 0.0001

int compare_matrix(double **matrix_a, double **matrix_b, int row, int column)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			if (fabs(matrix_a[i][j] - matrix_b[i][j]) > EPS)
				return FAIL;
	return OK;
}

void test_determinant(void)
{
	int error_count = 0;

	// Первый тест функции вычисления определителя. Положительные элементы.
	{
		int status = OK, row, column;
		double **matrix;
		status = io_form_matrix("tests/determinant/in_1.txt", &matrix, &row, &column);
		if (status != OK)
			error_count += 1;
		double det;
		status = func_determinant(matrix, &det, row);
		if (status == OK)
		{
			double right_det = 0.0;
			if (fabs(det - right_det) > EPS)
				error_count += 1;
		}
		else
			error_count += 1;
		if (matrix != NULL)
			free_matrix(matrix, row);
	}

	// Второй тест функции вычисления определителя. Матрица заполнена 0-лями.
	{
		int status = OK, row, column;
		double **matrix;
		status = io_form_matrix("tests/determinant/in_2.txt", &matrix, &row, &column);
		if (status != OK)
			error_count += 1;
		double det;
		status = func_determinant(matrix, &det, row);
		if (status == OK)
		{
			double right_det = 0.0;
			if (fabs(det - right_det) > EPS)
				error_count += 1;
		}
		else
			error_count += 1;
		if (matrix != NULL)
			free_matrix(matrix, row);
	}

	// Третий тест функции вычисления определителя. Главная диагональ матрицы равна 0.
	{
		int status = OK, row, column;
		double **matrix;
		status = io_form_matrix("tests/determinant/in_3.txt", &matrix, &row, &column);
		if (status != OK)
			error_count += 1;
		double det;
		status = func_determinant(matrix, &det, row);
		if (status == OK)
		{
			double right_det = -32.0;
			if (fabs(det - right_det) > EPS)
				error_count += 1;
		}
		else
			error_count += 1;
		if (matrix != NULL)
			free_matrix(matrix, row);
	}
	// Четвёртый тест функции вычисления определителя. Все элементы отрицательные.
	{
		int status = OK, row, column;
		double **matrix;
		status = io_form_matrix("tests/determinant/in_4.txt", &matrix, &row, &column);
		if (status != OK)
			error_count += 1;
		double det;
		status = func_determinant(matrix, &det, row);
		if (status == OK)
		{
			double right_det = 82;
			if (fabs(det - right_det) > EPS)
				error_count += 1;
		}
		else
			error_count += 1;
		if (matrix != NULL)
			free_matrix(matrix, row);
	}

	// Пятый тест функции вычисления определителя. Смешанные элементы матрицы.
	{
		int status = OK, row, column;
		double **matrix;
		status = io_form_matrix("tests/determinant/in_5.txt", &matrix, &row, &column);
		if (status != OK)
			error_count += 1;
		double det;
		status = func_determinant(matrix, &det, row);
		if (status == OK)
		{
			double right_det = 1360;
			if (fabs(det - right_det) > EPS)
				error_count += 1;
		}
		else
			error_count += 1;
		if (matrix != NULL)
			free_matrix(matrix, row);
	}

	// Шестой тест функции вычисления определителя. Смешанные дробные элементы матрицы.
	{
		int status = OK, row, column;
		double **matrix;
		status = io_form_matrix("tests/determinant/in_6.txt", &matrix, &row, &column);
		if (status != OK)
			error_count += 1;
		double det;
		status = func_determinant(matrix, &det, row);
		if (status == OK)
		{
			double right_det = -334824.960175;
			if (fabs(det - right_det) > EPS)
				error_count += 1;
		}
		else
			error_count += 1;
		if (matrix != NULL)
			free_matrix(matrix, row);
	}

	// Седьмой тест функции вычисления определителя. Единичная матрица.
	{
		int status = OK, row, column;
		double **matrix;
		status = io_form_matrix("tests/determinant/in_7.txt", &matrix, &row, &column);
		if (status != OK)
			error_count += 1;
		double det;
		status = func_determinant(matrix, &det, row);
		if (status == OK)
		{
			double right_det = 0;
			if (fabs(det - right_det) > EPS)
				error_count += 1;
		}
		else
			error_count += 1;
		if (matrix != NULL)
			free_matrix(matrix, row);
	}
/*
	// Восьмой тест функции вычисления определителя. Матрица 10 на 10.
	{
		int status = OK, row, column;
		double **matrix;
		status = io_form_matrix("tests/determinant/in_8.txt", &matrix, &row, &column);
		if (status != OK)
			error_count += 1;
		double det = func_determinant(matrix, row);
		double right_det = 0;
		if (fabs(det - right_det) > EPS)
			error_count += 1;
		if (matrix != NULL)
			free_matrix(matrix);
	}
 */

	printf("TEST %s: %s\n", __func__, error_count ? "FAIL" : "OK");
}

void test_sum_matrix(void)
{
	int error_count = 0;

	// Первый тест функции сложения матриц. Положительные элементы.
	{
		int status = OK, row_a, column_a, row_b, column_b, row_r, column_r;
		double **matrix_a = NULL, **matrix_b = NULL;
		status = io_form_matrix("tests/sum_matrix/in_1A.txt", &matrix_a, &row_a, &column_a);
		if (status == OK)
			status = io_form_matrix("tests/sum_matrix/in_1B.txt", &matrix_b, &row_b, &column_b);

		if (status == OK && row_a == row_b && column_a == column_b)
		{
			double **matrix_c = io_allocate_matrix(row_a, column_a);
			if (matrix_c != NULL)
			{
				sum(matrix_a, matrix_b, matrix_c, row_a, column_a);
			}
			else
				status = ERR_MEMORY;

			if (status == OK)
			{
				double **matrix_r = NULL;
				status = io_form_matrix("tests/sum_matrix/in_1R.txt", &matrix_r, &row_r, &column_r);
				if (status == OK)
					status = compare_matrix(matrix_c, matrix_r, row_r, row_r);
				if (matrix_r != NULL)
					free_matrix(matrix_r, row_r);
			}
			if (matrix_c != NULL)
				free_matrix(matrix_c, row_a);
		}
		if (matrix_a != NULL)
			free_matrix(matrix_a, row_a);
		if (matrix_b != NULL)
			free_matrix(matrix_b, row_b);

		if (status != OK)
			error_count += 1;
	}

	// Второй тест функции сложения матриц. 0-вые матрицы.
	{
		int status = OK, row_a, column_a, row_b, column_b, row_r, column_r;
		double **matrix_a = NULL, **matrix_b = NULL;
		status = io_form_matrix("tests/sum_matrix/in_2A.txt", &matrix_a, &row_a, &column_a);
		if (status == OK)
			status = io_form_matrix("tests/sum_matrix/in_2B.txt", &matrix_b, &row_b, &column_b);

		if (status == OK && row_a == row_b && column_a == column_b)
		{
			double **matrix_c = io_allocate_matrix(row_a, column_a);
			if (matrix_c != NULL)
			{
				sum(matrix_a, matrix_b, matrix_c, row_a, column_a);
			}
			else
				status = ERR_MEMORY;

			if (status == OK)
			{
				double **matrix_r = NULL;
				status = io_form_matrix("tests/sum_matrix/in_2R.txt", &matrix_r, &row_r, &column_r);
				if (status == OK)
					status = compare_matrix(matrix_c, matrix_r, row_r, row_r);
				if (matrix_r != NULL)
					free_matrix(matrix_r, row_r);
			}
			if (matrix_c != NULL)
				free_matrix(matrix_c, row_a);
		}
		if (matrix_a != NULL)
			free_matrix(matrix_a, row_a);
		if (matrix_b != NULL)
			free_matrix(matrix_b, row_b);

		if (status != OK)
			error_count += 1;
	}

	// Третий тест функции сложения матриц. Функции размера 2х2.
	{
		int status = OK, row_a, column_a, row_b, column_b, row_r, column_r;
		double **matrix_a = NULL, **matrix_b = NULL;
		status = io_form_matrix("tests/sum_matrix/in_3A.txt", &matrix_a, &row_a, &column_a);
		if (status == OK)
			status = io_form_matrix("tests/sum_matrix/in_3B.txt", &matrix_b, &row_b, &column_b);

		if (status == OK && row_a == row_b && column_a == column_b)
		{
			double **matrix_c = io_allocate_matrix(row_a, column_a);
			if (matrix_c != NULL)
			{
				sum(matrix_a, matrix_b, matrix_c, row_a, column_a);
			}
			else
				status = ERR_MEMORY;

			if (status == OK)
			{
				double **matrix_r = NULL;
				status = io_form_matrix("tests/sum_matrix/in_3R.txt", &matrix_r, &row_r, &column_r);
				if (status == OK)
					status = compare_matrix(matrix_c, matrix_r, row_r, row_r);
				if (matrix_r != NULL)
					free_matrix(matrix_r, row_r);
			}
			if (matrix_c != NULL)
				free_matrix(matrix_c, row_a);
		}
		if (matrix_a != NULL)
			free_matrix(matrix_a, row_a);
		if (matrix_b != NULL)
			free_matrix(matrix_b, row_b);

		if (status != OK)
			error_count += 1;
	}

	// Четвертый тест функции сложения матриц. Функции размера 4х4.
	{
		int status = OK, row_a, column_a, row_b, column_b, row_r, column_r;
		double **matrix_a = NULL, **matrix_b = NULL;
		status = io_form_matrix("tests/sum_matrix/in_4A.txt", &matrix_a, &row_a, &column_a);
		if (status == OK)
			status = io_form_matrix("tests/sum_matrix/in_4B.txt", &matrix_b, &row_b, &column_b);

		if (status == OK && row_a == row_b && column_a == column_b)
		{
			double **matrix_c = io_allocate_matrix(row_a, column_a);
			if (matrix_c != NULL)
			{
				sum(matrix_a, matrix_b, matrix_c, row_a, column_a);
			}
			else
				status = ERR_MEMORY;

			if (status == OK)
			{
				double **matrix_r = NULL;
				status = io_form_matrix("tests/sum_matrix/in_4R.txt", &matrix_r, &row_r, &column_r);
				if (status == OK)
					status = compare_matrix(matrix_c, matrix_r, row_r, row_r);
				if (matrix_r != NULL)
					free_matrix(matrix_r, row_r);
			}
			if (matrix_c != NULL)
				free_matrix(matrix_c, row_a);
		}
		if (matrix_a != NULL)
			free_matrix(matrix_a, row_a);
		if (matrix_b != NULL)
			free_matrix(matrix_b, row_b);

		if (status != OK)
			error_count += 1;
	}

	printf("TEST %s: %s\n", __func__, error_count ? "FAIL" : "OK");
}

void test_mult_matrix(void)
{
	// io_matrix_fprintf(stdout, matrixC, rowB, columnA);
	int error_count = 0;

	// Первый тест функции умножения матриц. Положительные элементы.
	{
		int status = OK, row_a, column_a, row_b, column_b, row_r, column_r;
		double **matrix_a = NULL, **matrix_b = NULL, **matrix_c = NULL;
		status = io_form_matrix("tests/mult_matrix/in_1A.txt", &matrix_a, &row_a, &column_a);
		if (status == OK)
			status = io_form_matrix("tests/mult_matrix/in_1B.txt", &matrix_b, &row_b, &column_b);

		if (status == OK && row_a == column_b)
		{
			matrix_c = io_allocate_matrix(row_b, column_a);
			if (matrix_c != NULL)
				mult(matrix_a, matrix_b, matrix_c, row_b, column_a, column_b);
		}
		else
			status = ERR_MATRIX_SIZE;

		if (status == OK)
		{
			double **matrix_r = NULL;
			status = io_form_matrix("tests/mult_matrix/in_1R.txt", &matrix_r, &row_r, &column_r);
			if (status == OK && row_r == row_b && column_r == column_a)
				status = compare_matrix(matrix_c, matrix_r, row_r, column_r);
			else if (status == OK)
				status = ERR_MATRIX_SIZE;
			if (matrix_r != NULL)
				free_matrix(matrix_r, row_r);
		}
		if (matrix_a != NULL)
			free_matrix(matrix_a, row_a);
		if (matrix_b != NULL)
			free_matrix(matrix_b, row_b);
		if (matrix_c != NULL)
			free_matrix(matrix_c, row_b);
		if (status != OK)
			error_count += 1;
	}

	// Второй тест функции умножения матриц. Матрицы разных размеров.
	{
		int status = OK, row_a, column_a, row_b, column_b, row_r, column_r;
		double **matrix_a = NULL, **matrix_b = NULL, **matrix_c = NULL;
		status = io_form_matrix("tests/mult_matrix/in_2A.txt", &matrix_a, &row_a, &column_a);
		if (status == OK)
			status = io_form_matrix("tests/mult_matrix/in_2B.txt", &matrix_b, &row_b, &column_b);

		if (status == OK && column_a == row_b)
		{
			matrix_c = io_allocate_matrix(row_a, column_b);
			if (matrix_c != NULL)
				mult(matrix_a, matrix_b, matrix_c, row_a, column_b, row_b);
		}
		else
			status = ERR_MATRIX_SIZE;

		if (status == OK)
		{
			double **matrix_r = NULL;
			status = io_form_matrix("tests/mult_matrix/in_2R.txt", &matrix_r, &row_r, &column_r);
			if (status == OK && row_r == row_a && column_r == column_b)
				status = compare_matrix(matrix_c, matrix_r, row_r, column_r);
			else if (status == OK)
				status = ERR_MATRIX_SIZE;

			if (matrix_r != NULL)
			    free_matrix(matrix_r, row_r);
		}
		if (matrix_a != NULL)
			free_matrix(matrix_a, row_a);
		if (matrix_b != NULL)
			free_matrix(matrix_b, row_b);
		if (matrix_c != NULL)
			free_matrix(matrix_c, row_a);
		if (status != OK)
			error_count += 1;
	}

	// Третий тест функции умножения матриц. Смешанные элементы.
	{
		int status = OK, row_a, column_a, row_b, column_b, row_r, column_r;
		double **matrix_a = NULL, **matrix_b = NULL, **matrix_c = NULL;
		status = io_form_matrix("tests/mult_matrix/in_3A.txt", &matrix_a, &row_a, &column_a);
		if (status == OK)
			status = io_form_matrix("tests/mult_matrix/in_3B.txt", &matrix_b, &row_b, &column_b);

		if (status == OK && row_a == column_b)
		{
			matrix_c = io_allocate_matrix(row_b, column_a);
			if (matrix_c != NULL)
				mult(matrix_a, matrix_b, matrix_c, row_b, column_a, column_b);
		}
		else
			status = ERR_MATRIX_SIZE;

		if (status == OK)
		{
			double **matrix_r = NULL;
			status = io_form_matrix("tests/mult_matrix/in_3R.txt", &matrix_r, &row_r, &column_r);
			if (status == OK && row_r == row_b && column_r == column_a)
				status = compare_matrix(matrix_c, matrix_r, row_r, column_r);
			else if (status == OK)
				status = ERR_MATRIX_SIZE;

			if (matrix_r != NULL)
			    free_matrix(matrix_r, row_r);
		}
		if (matrix_a != NULL)
			free_matrix(matrix_a, row_a);
		if (matrix_b != NULL)
			free_matrix(matrix_b, row_b);
		if (matrix_c != NULL)
			free_matrix(matrix_c, row_b);
		if (status != OK)
			error_count += 1;
	}

	// Четвертый тест функции умножения матриц. Нулевые элементы.
	{
		int status = OK, row_a, column_a, row_b, column_b, row_r, column_r;
		double **matrix_a = NULL, **matrix_b = NULL, **matrix_c = NULL;
		status = io_form_matrix("tests/mult_matrix/in_4A.txt", &matrix_a, &row_a, &column_a);
		if (status == OK)
			status = io_form_matrix("tests/mult_matrix/in_4B.txt", &matrix_b, &row_b, &column_b);

		if (status == OK && row_a == column_b)
		{
			matrix_c = io_allocate_matrix(row_b, column_a);
			if (matrix_c != NULL)
				mult(matrix_a, matrix_b, matrix_c, row_b, column_a, column_b);
		}
		else
			status = ERR_MATRIX_SIZE;

		if (status == OK)
		{
			double **matrix_r = NULL;
			status = io_form_matrix("tests/mult_matrix/in_4R.txt", &matrix_r, &row_r, &column_r);
			if (status == OK && row_r == row_b && column_r == column_a)
				status = compare_matrix(matrix_c, matrix_r, row_r, column_r);
			else if (status == OK)
				status = ERR_MATRIX_SIZE;

			if (matrix_r != NULL)
			    free_matrix(matrix_r, row_r);
		}
		if (matrix_a != NULL)
			free_matrix(matrix_a, row_a);
		if (matrix_b != NULL)
			free_matrix(matrix_b, row_b);
		if (matrix_c != NULL)
			free_matrix(matrix_c, row_b);
		if (status != OK)
			error_count += 1;
	}

	printf("TEST %s: %s\n", __func__, error_count ? "FAIL" : "OK");
}

void test_inverse_matrix(void)
{
	int error_count = 0;

	// Первый тест функции обращения матрицы. Матрица 2x2.
	{
		int status = OK;
		int row, column;
		double **matrix = NULL;

		status = io_form_matrix("tests/inverse_matrix/in_1A.txt", &matrix, &row, &column);
		if (status == OK)
		{
			double **matrix_e = NULL;
			status = form_matrix_e(&matrix_e, row);
			if (status == OK)
				inverse(matrix, &matrix_e, row);

			if (status == OK)
			{
				double **matrix_r = NULL;
				int row_r, column_r;
				status = io_form_matrix("tests/inverse_matrix/in_1R.txt", &matrix_r, &row_r, &column_r);
				if (status == OK && row_r == row && column_r == column)
					status = compare_matrix(matrix_e, matrix_r, row_r, column_r);
				if (matrix_r != NULL)
					free_matrix(matrix_r, row_r);
			}
			if (matrix_e != NULL)
				free_matrix(matrix_e, row);
		}
		if (matrix != NULL)
			free_matrix(matrix, row);

		if (status != OK)
			error_count += 1;
	}

	// Второй тест функции обращения матрицы. Матрица 3x3.
	{
		int status = OK;
		int row, column;
		double **matrix = NULL;

		status = io_form_matrix("tests/inverse_matrix/in_2A.txt", &matrix, &row, &column);
		if (status == OK)
		{
			double **matrix_e = NULL;
			status = form_matrix_e(&matrix_e, row);
			if (status == OK)
				inverse(matrix, &matrix_e, row);

			if (status == OK)
			{
				double **matrix_r = NULL;
				int row_r, column_r;
				status = io_form_matrix("tests/inverse_matrix/in_2R.txt", &matrix_r, &row_r, &column_r);
				if (status == OK && row_r == row && column_r == column)
					status = compare_matrix(matrix_e, matrix_r, row_r, column_r);
				if (matrix_r != NULL)
					free_matrix(matrix_r, row_r);
			}
			if (matrix_e != NULL)
				free_matrix(matrix_e, row);
		}
		if (matrix != NULL)
			free_matrix(matrix, row);
		if (status != OK)
			error_count += 1;
	}

	// Третий тест функции обращения матрицы. Матрица 4x4.
	{
		int status = OK;
		int row, column;
		double **matrix = NULL;

		status = io_form_matrix("tests/inverse_matrix/in_3A.txt", &matrix, &row, &column);
		if (status == OK)
		{
			double **matrix_e = NULL;
			status = form_matrix_e(&matrix_e, row);
			if (status == OK)
				inverse(matrix, &matrix_e, row);

			if (status == OK)
			{
				double **matrix_r = NULL;
				int row_r, column_r;
				status = io_form_matrix("tests/inverse_matrix/in_3R.txt", &matrix_r, &row_r, &column_r);
				if (status == OK && row_r == row && column_r == column)
					status = compare_matrix(matrix_e, matrix_r, row_r, column_r);
				if (matrix_r != NULL)
					free_matrix(matrix_r, row_r);
			}
			if (matrix_e != NULL)
				free_matrix(matrix_e, row);
		}
		if (matrix != NULL)
			free_matrix(matrix, row);

		if (status != OK)
			error_count += 1;
	}

	printf("TEST %s: %s\n", __func__, error_count ? "FAIL" : "OK");
}

int main(void)
{
	test_determinant();
	test_sum_matrix();
	test_mult_matrix();
	test_inverse_matrix();

	return 0;
}

