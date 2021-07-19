/* найти среднее значение чисел, расположенных между минимальным и максимальным
числами («между» - не по значению, а по расположению)*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define OK 0
#define ERR_DATA 2
#define ERR_FILE 1
#define ERR_WRONG_CMD 3
#define EPS 0.00001

int finding_pos(FILE *f, int *min_pos, int *max_pos)
{
    float num, max, min;
    int i = 2;
    *min_pos = 0;
    *max_pos = 1;

    if (fscanf(f, "%f%f", &min, &max) == 2) 
    {
        if (min > max) 
        {
            num = max;
            max = min;
            min = num;
            *min_pos = 1;
            *max_pos = 0;
        }

        while (fscanf(f, "%f", &num) == 1)
        {
            if (num > max) 
            {
                max = num;
                *max_pos = i;
            } 
            else if (num < min) 
            {
                min = num;
                *min_pos = i;
            } 
            else if ((fabs(num - max) < EPS) && (*max_pos > *min_pos))
                *max_pos = i;
            else if ((fabs(num - min) < EPS) && (*min_pos > *max_pos))
                *min_pos = i;
            i++;
        }

        return OK;
    }

    return ERR_DATA;
}

float finding_average(FILE *f, int min_pos, int max_pos)
{
    float average, sum = 0, num;
    int i = 0, difference;

    while (fscanf(f, "%f", &num) == 1)
    {
        if (i > min_pos && i < max_pos)
            sum += num;
        i++;
    }

    difference = max_pos - min_pos - 1;
    average = sum / difference;

    return average;
}

int main(int argc, char *argv[])
{
    FILE *f;
    int rc = OK, per, min_pos, max_pos;
    float average;

    if (argc != 2)
    {
        printf("app.exe file_name\n");
        return ERR_WRONG_CMD;
    }

    f = fopen(argv[1], "r");
    if (f != NULL)
    {
        rc = finding_pos(f, &min_pos, &max_pos);
        if (max_pos < min_pos)
        {
            per = max_pos;
            max_pos = min_pos;
            min_pos = per;
        }

        if (min_pos == max_pos)
        {
            rc = ERR_DATA;
            printf("Wrong data in file!");
        }
        else if (min_pos + 1 == max_pos)
        {
            rc = ERR_DATA;
            printf("There are not numbers between max and min!");
        }
        else if (rc == OK)
        {
            if (fseek(f, 0, SEEK_SET) == false)
            {
                average = finding_average(f, min_pos, max_pos);
                printf("Result: %f", average);
            }
            else
            {
                printf("Problems with file");
                return ERR_FILE;
            }
        }
        else if (rc == ERR_DATA)
        {
            printf("Not enough data in file!");
        }
        fclose(f);
    }
    else
    {
        printf("Problems with file");
        return ERR_FILE;
    }

    return rc;
}

