#include <stdio.h>
#include <time.h>
#include "sort.h"
#define MAX_RANDOM_NUMBER 100
#define OK 0
#define ERR_RANGE 1
#define N 100

/**
Определяет тик процессора. 
*/
unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

/**
Создает массив случайных элементов.

@param array [out] массив с элементами
@param size [in] количество элементов
*/
void create_random_array(int *array, int size)
{
	for (int i = 0; i < size; i++)
		array[i] = rand() % MAX_RANDOM_NUMBER;
}

/**
Создает массив упорядоченных элементов.

@param array [out] массив с элементами
@param size [in] количество элементов
*/
void create_sorted_array(int *array, int size)
{
	for (int i = 0; i < size; i++)
		array[i] = i;
}

/**
Создает массив неупорядоченных элементов.

@param array [out] массив с элементами
@param size [in] количество элементов
*/
void create_unsorted_array(int *array, int size)
{
	for (int i = size; i > 0; i--)
		array[i] = i;
}

/**
Считает время сортировки случайных, упорядоченных и неупорядоченных массивов разного размера для сортировок qsort и пузырьком.
*/
int test_sort(void)
{
	int size;
	printf("Input size of array: ");
	if (scanf("%d", &size) != 1)
		return ERR_RANGE;
	if (size <= 0)
		return ERR_RANGE;
	unsigned long long tb, te, full_time = 0;
	int random_array[size];
	int sorted_array[size];
	int unsorted_array[size];

	printf("\nRandom array\n");
	for (int i = 0; i < N; i++)
	{
		create_random_array(random_array, size);
		int *pr = random_array, *pre = pr + size;
		tb = tick();
		mysort(pr, pre - pr, sizeof(int), sort_compare_int);
		te = tick();
		// printf("test %d 'time': \t%I64d\n", i, (te - tb));
		full_time += (te - tb);
	}
	printf("\nAverage time mysort: \t%I64d\n\n", full_time / N);

	full_time = 0;
	for (int i = 0; i < N; i++)
	{
		create_random_array(random_array, size);
		int *pr = random_array, *pre = pr + size;
		tb = tick();
		qsort(pr, pre - pr, sizeof(int), sort_compare_int);
		te = tick();
		// printf("test %d 'time': \t%I64d\n", i, (te - tb));
		full_time += (te - tb);
	}
	printf("\nAverage time qsort: \t%I64d\n\n", full_time / N);

	printf("\nSorted array\n");
	full_time = 0;
	for (int i = 0; i < N; i++)
	{
		create_sorted_array(sorted_array, size);
		int *pr = sorted_array, *pre = pr + size;
		tb = tick();
		mysort(pr, pre - pr, sizeof(int), sort_compare_int);
		te = tick();
		// printf("test %d 'time': \t%I64d\n", i, (te - tb));
		full_time += (te - tb);
	}
	printf("\nAverage time mysort: \t%I64d\n\n", full_time / N);

	full_time = 0;
	for (int i = 0; i < N; i++)
	{
		create_sorted_array(sorted_array, size);
		int *pr = sorted_array, *pre = pr + size;
		tb = tick();
		qsort(pr, pre - pr, sizeof(int), sort_compare_int);
		te = tick();
		// printf("test %d 'time': \t%I64d\n", i, (te - tb));
		full_time += (te - tb);
	}
	printf("\nAverage time qsort: \t%I64d\n\n", full_time / N);

	printf("\nUnsorted array\n");
	full_time = 0;
	for (int i = 0; i < N; i++)
	{
		create_unsorted_array(unsorted_array, size);
		int *pr = unsorted_array, *pre = pr + size;
		tb = tick();
		mysort(pr, pre - pr, sizeof(int), sort_compare_int);
		te = tick();
		// printf("test %d 'time': \t%I64d\n", i, (te - tb));
		full_time += (te - tb);
	}
	printf("\nAverage time mysort: \t%I64d\n\n", full_time / N);

	full_time = 0;
	for (int i = 0; i < N; i++)
	{
		create_unsorted_array(unsorted_array, size);
		int *pr = unsorted_array, *pre = pr + size;
		tb = tick();
		qsort(pr, pre - pr, sizeof(int), sort_compare_int);
		te = tick();
		// printf("test %d 'time': \t%I64d\n", i, (te - tb));
		full_time += (te - tb);
	}
	printf("\nAverage time qsort: \t%I64d\n\n", full_time / N);

	return OK;
}

int main(void)
{
	setbuf(stdout, NULL);
	srand(time(NULL));
	int rc = OK;
	rc = test_sort();

	return rc;
}
