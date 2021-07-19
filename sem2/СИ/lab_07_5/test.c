#include "filter.h"
#include "error.h"
#include "config.h"
#include "sort.h"
#include "array_io.h"
#include "array_io.h"
#include <math.h>
#define EPS 0.0001
#define N 5
#define M 10
#define K 2
#define B 1
#define FAIL 1
#define OK 0

/**
Сравнивают элементы массивов типа int. 

@param array [in] массив элементами, которые обрабатывает программа
@param array_right [in] массив с правильными данными
@param size [in] размер массивов

@return Возвращает OK, если все элементы одинаковы, либо FAIL, если не совпадают элементы.
*/
int compare_int(const int *array, const int *array_right, int size)
{
	for (int i = 0; i < size; i++)
		if (array[i] != array_right[i])
		{
			return FAIL;
		}
	return OK;
}

/**
Сравнивают элементы массивов типа double. 

@param array [in] массив элементами, которые обрабатывает программа
@param array_right [in] массив с правильными данными
@param size [in] размер массивов

@return Возвращает OK, если все элементы одинаковы, либо FAIL, если не совпадают элементы.
*/
int compare_double(const double *array, const double *array_right, int size)
{
	for (int i = 0; i < size; i++)
		if (fabs(array[i] - array_right[i]) > EPS)
		{
			return FAIL;
		}
	return OK;
}

/**
Сравнивают элементы массивов типа char. 

@param array [in] массив элементами, которые обрабатывает программа
@param array_right [in] массив с правильными данными
@param size [in] размер массивов

@return Возвращает OK, если все элементы одинаковы, либо FAIL, если не совпадают элементы.
*/
int compare_char(const char *array, const char *array_right, int size)
{
	for (int i = 0; i < size; i++)
		if (array[i] != array_right[i])
			return FAIL;
	return OK;
}

/**
Модульное тестирование функции key. 
*/
void test_key(void)
{
	int error_count = 0;

	// Первый тест фильтра. После фильтрации элементов не осталось.
	{
		int array[N] = { 1, 2, 3, 4, 5 };
		int array_filtered[N];
		int *pa = array, *paf = array_filtered;
		int *pae = pa + N, *pafe = NULL;
		int rc = OK;

		rc = key(pa, pae, &paf, &pafe);

		if (rc == OK)
			error_count += 1;
	}

	// Второй тест фильтра. После фильтрации остался один элемент.
	{
		int array[N] = { 5, 4, 3, 2, 1 }, array_filtered[N], array_right[N] = { 2 };
		int *pa = array, *paf = array_filtered, *par = array_right;
		int *pae = pa + N, *pafe = NULL;
		int size_f, rc = OK, size_r = 1;

		rc = key(pa, pae, &paf, &pafe);

		size_f = pafe - paf;
		if (rc == OK)
		{
			if (size_f == size_r)
			{
				rc = compare_int(paf, par, size_f);
				if (rc != OK)
					error_count += 1;
			}
			else
				error_count += 1;
		}
		else
			error_count += 1;

		if (paf != NULL)
			free(paf);
	}

	// Третий тест фильтра. Случайный массив.
	{
		int array[N] = { 9, 2, -2, 8, 0 }, array_filtered[N], array_right[N] = { 9, 8 };
		int *pa = array, *paf = array_filtered, *par = array_right;
		int *pae = pa + N, *pafe = NULL;
		int size_f, rc = OK, size_r = 2;

		rc = key(pa, pae, &paf, &pafe);

		size_f = pafe - paf;
		if (rc == OK)
		{
			if (size_f == size_r)
			{
				rc = compare_int(paf, par, size_f);
				if (rc != OK)
					error_count += 1;
			}
			else
				error_count += 1;
		}
		else
			error_count += 1;

		if (paf != NULL)
			free(paf);
	}

	// Четвёртый тест фильтра. Остаются все элементы, кроме последнего.
	{
		int array[N] = { 8, 4, 2, 1, 0 }, array_filtered[N], array_right[N] = { 8, 4, 2, 1 };
		int *pa = array, *paf = array_filtered, *par = array_right;
		int *pae = pa + N, *pafe = NULL;
		int size_f, rc = OK, size_r = 4;

		rc = key(pa, pae, &paf, &pafe);

		size_f = pafe - paf;
		if (rc == OK)
		{
			if (size_f == size_r)
			{
				rc = compare_int(paf, par, size_f);
				if (rc != OK)
					error_count += 1;
			}
			else
				error_count += 1;
		}
		else
			error_count += 1;

		if (paf != NULL)
			free(paf);
	}

	// Пятый тест фильтра. Остался только первый элемент.
	{
		int array[N] = { 216, 6, 7, 8, 9 }, array_filtered[N], array_right[N] = { 216 };
		int *pa = array, *paf = array_filtered, *par = array_right;
		int *pae = pa + N, *pafe = NULL;
		int size_f, rc = OK, size_r = 1;

		rc = key(pa, pae, &paf, &pafe);

		size_f = pafe - paf;
		if (rc == OK)
		{
			if (size_f == size_r)
			{
				rc = compare_int(paf, par, size_f);
				if (rc != OK)
					error_count += 1;
			}
			else
				error_count += 1;
		}
		else
			error_count += 1;

		if (paf != NULL)
			free(paf);
	}

	// Шестой тест фильтра. Только отрицательные элементы.
	{
		int array[N] = { -6, -12, -3, -3, -5 }, array_filtered[N], array_right[N] = { -6, -3, -3 };
		int *pa = array, *paf = array_filtered, *par = array_right;
		int *pae = pa + N, *pafe = NULL;
		int size_f, rc = OK, size_r = 3;

		rc = key(pa, pae, &paf, &pafe);

		size_f = pafe - paf;
		if (rc == OK)
		{
			if (size_f == size_r)
			{
				rc = compare_int(paf, par, size_f);
				if (rc != OK)
					error_count += 1;
			}
			else
				error_count += 1;
		}
		else
			error_count += 1;

		if (paf != NULL)
			free(paf);
	}

    printf("TEST %s: %s\n", __func__, error_count ? "FAILED" : "OK");	
}

/**
Тестирует массивы типа int. 
*/
void test_int_sort(void)
{
	int error_count = 0;

	// Первый тест сортировки. Значения элементов массива возрастают. 
	{
		int array[M] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, array_right[M] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		int *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(int), sort_compare_int);

		rc = compare_int(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Второй тест сортировки. Значения элементов массива убывают.
	{
		int array[M] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }, array_right[M] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		int *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(int), sort_compare_int);

		rc = compare_int(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Третий тест сортировки. Значения элементов массива случайны. 
	{
		int array[M] = { -4, -9, 4, -4, 7, 4, 0, -4, -5, -2 }, array_right[M] = { -9, -5, -4, -4, -4, -2, 0, 4, 4, 7 };
		int *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(int), sort_compare_int);

		rc = compare_int(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Четвертый тест сортировки. Значения элементов массива одинаковы.
	{
		int array[M] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 }, array_right[M] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
		int *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(int), sort_compare_int);

		rc = compare_int(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Пятый тест сортировки. Значения элементов массива убывают (для двух элементов).
	{
		int array[K] = { 9, 1 }, array_right[K] = { 1, 9 };
		int *pa = array, *par = array_right;
		int size = K, rc = OK;

		mysort(pa, size, sizeof(int), sort_compare_int);

		rc = compare_int(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Шестой тест сортировки. Значения элементов массива возрастают (для двух элементов).
	{
		int array[K] = { 1, 9 }, array_right[K] = { 1, 9 };
		int *pa = array, *par = array_right;
		int size = K, rc = OK;

		mysort(pa, size, sizeof(int), sort_compare_int);

		rc = compare_int(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Седьмой тест сортировки. Один элемент массива.
	{
		int array[B] = { 4 }, array_right[B] = { 4 };
		int *pa = array, *par = array_right;
		int size = B, rc = OK;

		mysort(pa, size, sizeof(int), sort_compare_int);

		rc = compare_int(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}
	// Пустой массив. 
	{
		int array[M], array_right[M];
		int *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(int), sort_compare_int);

		rc = compare_int(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	printf("TEST %s: %s\n", __func__, error_count ? "FAILED" : "OK");
}

/**
Тестирует массивы типа double. 
*/
void test_double_sort(void)
{
	int error_count = 0;

	// Первый тест сортировки. Значения элементов массива возрастают. 
	{
		double array[M] = { 1.3, 2.1, 3.8, 4.3, 5.8, 6.1, 7.9, 8.5, 9.623, 10.1 }, array_right[M] = { 1.3, 2.1, 3.8, 4.3, 5.8, 6.1, 7.9, 8.5, 9.623, 10.1 };
		double *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(double), sort_compare_double);

		rc = compare_double(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Второй тест сортировки. Значения элементов массива убывают.
	{
		double array[M] = { 15.12, 11.22, 8.3, 5.12, 3.1111, 1.333, 0.12, -3.11, -7.21, -9.87 }, array_right[M] = { -9.87, -7.21, -3.11, 0.12, 1.333, 3.1111, 5.12, 8.3, 11.22, 15.12 };
		double *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(double), sort_compare_double);

		rc = compare_double(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Третий тест сортировки. Значения элементов массива случайны. 
	{
		double array[M] = { -4.56, -9.44, 8.121, -4.36, 7.943, 9.61, 0.66, -4.39, -5.32, -2.11 }, array_right[M] = { -9.44, -5.32, -4.56, -4.39, -4.36, -2.11, 0.66, 7.943, 8.121, 9.61 };
		double *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(double), sort_compare_double);

		rc = compare_double(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Четвертый тест сортировки. Значения элементов массива одинаковы.
	{
		double array[M] = { 5.55, 5.55, 5.55, 5.55, 5.55, 5.55, 5.55, 5.55, 5.55, 5.55 }, array_right[M] = { 5.55, 5.55, 5.55, 5.55, 5.55, 5.55, 5.55, 5.55, 5.55, 5.55 };
		double *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(double), sort_compare_double);

		rc = compare_double(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Пятый тест сортировки. Значения элементов массива убывают (для двух элементов).
	{
		double array[K] = { 5.12, 0.99 }, array_right[K] = { 0.99, 5.12 };
		double *pa = array, *par = array_right;
		int size = K, rc = OK;

		mysort(pa, size, sizeof(double), sort_compare_double);

		rc = compare_double(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Шестой тест сортировки. Значения элементов массива возрастают (для двух элементов).
	{
		double array[K] = { 7.21, 9.16 }, array_right[K] = { 7.21, 9.16 };
		double *pa = array, *par = array_right;
		int size = K, rc = OK;

		mysort(pa, size, sizeof(double), sort_compare_double);

		rc = compare_double(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Седьмой тест сортировки. Один элемент массива.
	{
		double array[B] = { 4.16 }, array_right[B] = { 4.16 };
		double *pa = array, *par = array_right;
		int size = B, rc = OK;

		mysort(pa, size, sizeof(double), sort_compare_double);

		rc = compare_double(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Восьмой тест сортировки. Пустой массив. 
	{
		double array[M], array_right[M];
		double *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(double), sort_compare_double);

		rc = compare_double(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	printf("TEST %s: %s\n", __func__, error_count ? "FAILED" : "OK");
}

/**
Тестирует массивы типа char. 
*/
void test_char_sort(void)
{
	int error_count = 0;

	// Первый тест сортировки. Значения элементов массива возрастают. 
	{
		char array[M] = { 'a', 'c', 'd', 'e', 'i', 'm', 'p', 'r', 't', 'z' }, array_right[M] = { 'a', 'c', 'd', 'e', 'i', 'm', 'p', 'r', 't', 'z' };
		char *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(char), sort_compare_char);

		rc = compare_char(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Второй тест сортировки. Значения элементов массива убывают.
	{
		char array[M] = { 'z', 'y', 'x', 'w', 't', 'p', 'k', 'c', 'b', 'a' }, array_right[M] = { 'a', 'b', 'c', 'k', 'p', 't', 'w', 'x', 'y', 'z' };
		char *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(char), sort_compare_char);

		rc = compare_char(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Третий тест сортировки. Значения элементов массива случайны. 
	{
		char array[M] = { 'h', 'r', 'k', 'm', 'a', 'r', 'v', 'd', 'q', 'o' }, array_right[M] = { 'a', 'd', 'h', 'k', 'm', 'o', 'q', 'r', 'r', 'v' };
		char *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(char), sort_compare_char);

		rc = compare_char(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Четвертый тест сортировки. Значения элементов массива одинаковы.
	{
		char array[M] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a' }, array_right[M] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a' };
		char *pa = array, *par = array_right;
		int size = M, rc = OK;

		mysort(pa, size, sizeof(char), sort_compare_char);

		rc = compare_char(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Пятый тест сортировки. Значения элементов массива убывают (для двух элементов).
	{
		char array[K] = { 'b', 'a' }, array_right[K] = { 'a', 'b' };
		char *pa = array, *par = array_right;
		int size = K, rc = OK;

		mysort(pa, size, sizeof(char), sort_compare_char);

		rc = compare_char(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Шестой тест сортировки. Значения элементов массива возрастают (для двух элементов).
	{
		char array[K] = { 'c', 'd' }, array_right[K] = { 'c', 'd' };
		char *pa = array, *par = array_right;
		int size = K, rc = OK;

		mysort(pa, size, sizeof(char), sort_compare_char);

		rc = compare_char(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	// Седьмой тест сортировки. Один элемент массива.
	{
		char array[B] = { 'h' }, array_right[B] = { 'h' };
		char *pa = array, *par = array_right;
		int size = B, rc = OK;

		mysort(pa, size, sizeof(char), sort_compare_char);

		rc = compare_char(pa, par, size);
		if (rc != OK)
			error_count += 1;
	}

	printf("TEST %s: %s\n", __func__, error_count ? "FAILED" : "OK");
}

void test_io()
{
	int error_count = 0;

	// Первый тест. Файл пустой.
	{
		FILE *file = fopen("data/in_1.txt", "r");
		if (file != NULL)
		{
			int *array = NULL, *array_end = NULL;
			int count, status = io_read(file, &array, &array_end, &count);
			if (status != ERR_EMPTY)
				error_count += 1;
			free(array);
			fclose(file);
		}
	}

	// Второй тест. Стандартный файл. Вещественные числа в массив не попадают
	{
		FILE *file = fopen("data/in_3.txt", "r");
		if (file != NULL)
		{
			int *array = NULL, *array_end = NULL;
			int count, status = io_read(file, &array, &array_end, &count);
			int array_right[] = { 4, 6, 7, 3, 1, 8 };
			if (status == OK)
				compare_int(array, array_right, count);

			if (status != OK)
				error_count += 1;
			free(array);
			fclose(file);
		}
	}

	// Третий тест. Файл с целыми числами.
	{
		FILE *file = fopen("data/in_3.txt", "r");
		if (file != NULL)
		{
			int *array = NULL, *array_end = NULL;
			int count, status = io_read(file, &array, &array_end, &count);
			int array_right[] = { 8, 3, 11, 6, 1, 8, 4, 11, 90, 2, 1, 36 };
			if (status == OK)
				compare_int(array, array_right, count);

			if (status != OK)
				error_count += 1;
			free(array);
			fclose(file);
		}
	}

	printf("TEST %s: %s\n", __func__, error_count ? "FAILED" : "OK");
}


int main(int argc, char **argv)
{
	setbuf(stdout, NULL);
	test_key();
	test_int_sort();
	test_double_sort();
	test_char_sort();
	test_io();

	return 0;
}