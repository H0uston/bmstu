#include <stdio.h>
#include "config.h"
#include "arr_input.h"
#include "process.h"
#include <assert.h>

// Проверка функции ввода. Сначала сравнивается количество считанных элементов, а затем и сами элементы.
void arr_input_test(void)
{
	int err_cnt = 0;
	
	// Тестирование функции с положительными элементами.
	{
		// Создание файла с тестовыми данными
		int check_massive[] = {1, 2, 3, 4, 5};
		FILE *f_1;
		f_1 = fopen("test1.txt", "w");
		for (int i = 0; i < sizeof(check_massive) / sizeof(check_massive[0]); i++)
			fprintf(f_1, "%d ", check_massive[i]);
		fclose(f_1);

		f_1 = fopen("test1.txt", "r");
		assert(f_1);
		int a[N];
		int *pbeg = a, *pend = a, i = 0;
		int right_count = sizeof(check_massive) / sizeof(check_massive[0]), test_count;
		
		arr_input(f_1, pbeg, &pend);
		test_count = pend - pbeg;
		if (test_count != right_count)
			err_cnt += 1;
		else 
			while (pbeg < pend)
			{
				if (*pbeg != check_massive[i])
				{
					err_cnt++;
					break;
				}
				i++;
				pbeg++;
			}
		fclose(f_1);
	}
	
	// Тестирование функции с отрицательными данными
	{
		int check_massive[] = {-1, -10, -12};
		FILE *f_2;
		f_2 = fopen("test2.txt", "w");
		for (int i = 0; i < sizeof(check_massive) / sizeof(check_massive[0]); i++)
			fprintf(f_2, "%d ", check_massive[i]);
		fclose(f_2);

		f_2 = fopen("test2.txt", "r");
		assert(f_2);
		int b[N];
		int *pbeg = b, *pend = b, i = 0;
		int right_count = sizeof(check_massive) / sizeof(check_massive[0]), test_count;
		
		arr_input(f_2, pbeg, &pend);
		test_count = pend - pbeg;
				if (test_count != right_count)
			err_cnt += 1;
		else 
			while (pbeg < pend)
			{
				if (*pbeg != check_massive[i])
				{
					err_cnt++;
					break;
				}
				i++;
				pbeg++;
			}

		fclose(f_2);
	}
	
	// Тестирование функции на смешанные данные
	{
		int check_massive[] = {-41, 12, 7, 32, 0, 56};
		FILE *f_3;
		f_3 = fopen("test3.txt", "w");
		for (int i = 0; i < sizeof(check_massive) / sizeof(check_massive[0]); i++)
			fprintf(f_3, "%d ", check_massive[i]);
		fclose(f_3);

		f_3 = fopen("test3.txt", "r");
		assert(f_3);
		int c[N];
		int *pbeg = c, *pend = c, i = 0;
		int right_count = sizeof(check_massive) / sizeof(check_massive[0]), test_count;
		
		arr_input(f_3, pbeg, &pend);
		test_count = pend - pbeg;
				if (test_count != right_count)
			err_cnt += 1;
		else 
			while (pbeg < pend)
			{
				if (*pbeg != check_massive[i])
				{
					err_cnt++;
					break;
				}
				i++;
				pbeg++;
			}

		fclose(f_3);
	}
	
	
    printf("TEST %s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}

// Тестирование функции обработки данных (Поиск количества различных чисел в файле)
void process_test(void)
{
	int err_cnt = 0;
	
	// Тестирование функции на одинаковые данные
	{
		int h[] = {6, 6, 6};
		int *pbeg = h, *pend = pbeg + sizeof(h)/sizeof(h[0]);
		int right_count = 1, test_count;
		
		test_count = process(pbeg, pend);
		
		if (test_count != right_count)
			err_cnt += 1;
	}

	// Тестирование функции на положительные данные
	{
		int a[] = {5, 3, 1, 51, 35, 26, 30, 1, 5};
		int *pbeg = a, *pend = pbeg + sizeof(a)/sizeof(a[0]);
		int right_count = 7, test_count;
		
		test_count = process(pbeg, pend);
		
		if (test_count != right_count)
			err_cnt += 1;
	}
	
	// Тестирование функции на отрицательные данные
	{
		int b[] = {-1, -2, -3, -4, -3, -2, -1, 0};
		int *pbeg = b, *pend = pbeg + sizeof(b)/sizeof(b[0]);
		int right_count = 5, test_count;
		
		test_count = process(pbeg, pend);
		
		if (test_count != right_count)
			err_cnt += 1;
	}
	
	// Тестирование функции на смешанные данные
	{
		int c[] = {-3, -2, -1, 0, 1, 2, 3, 4, 4, -2, -3, 0, 2, 3, 1, -1};
		int *pbeg = c, *pend = pbeg + sizeof(c)/sizeof(c[0]);
		int right_count = 8, test_count;
		
		test_count = process(pbeg, pend);
		
		if (test_count != right_count)
			err_cnt += 1;
	}

	// Тестирование функции на смешанные данные
	{
		int d[] = {11, -30, 12, 18, 0, 12, 18, 0, 12, -30, -36};
		int *pbeg = d, *pend = pbeg + sizeof(d)/sizeof(d[0]);
		int right_count = 6, test_count;
		
		test_count = process(pbeg, pend);
		
		if (test_count != right_count)
			err_cnt += 1;
	}
	
	
    printf("TEST %s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}
		
		

int main(void)
{
	arr_input_test();
	process_test();

	return 0;
}