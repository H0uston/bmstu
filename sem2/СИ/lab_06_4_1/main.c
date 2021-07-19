// Посчитать количество различных чисел в файле. Версия многофайлового проекта без заголовочного файла.
#include <stdio.h>
#define OK 0
#define N 100
#define ERR_FILE 1
#define ERR_RANGE 2
#define ERR_WRONG_CMD 3
#define ERR_VLE 4

int arr_input(FILE *f, int *pbeg, int **pend);

void arr_print(const int *pbeg, const int *pend);

int process(int * const pbeg, const int *pend);

int main(int argc, char *argv[])
{
    FILE *f;
    int rc = OK, arr[N], repetition, count;
    int *pbeg = arr, *pend = arr;
    if (argc != 2)
    {
        printf("Wrong parametrs! app.exe file_name.txt");
        rc = ERR_WRONG_CMD;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (f != NULL)
        {
            arr_input(f, pbeg, &pend);
            count = pbeg - pend;
            if (count != 0)
            {
                if (count == N)
                    printf("There are too many data in file. Some numbers will not be processed. \n");
                // arr_print(pbeg, pend);
                repetition = process(pbeg, pend);
                printf("\nCount of different numbers in file: %d", repetition);
            }
            else
            {
                printf("Not enough data in file!");
                rc = ERR_FILE;
            }
        }
        else
        {
            printf("File does not exist!");
            rc = ERR_FILE;
        }
        fclose(f);
    }

    return rc;
}
