// Посчитать количество различных чисел в файле. Версия многофайлового проекта без заголовочного файла.
#include <stdio.h>
#include "config.h"
#include "arr_input.h"
#include "arr_print.h"
#include "process.h"

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
