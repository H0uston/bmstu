#include <stdio.h>
#define OK 0
#define WRONG_CMD 1
#define ERR_DATA 2

float finding_average(FILE *f, int *rc)
{
    int num, count = 0;
    float sum = 0, result = 0;

    while (fscanf(f, "%d", &num) == 1)
    {
        if (num > 0)
        {
            sum += num;
            count += 1;
        }
    }
    if (count != 0)
        result = sum / count;
    else
        *rc = ERR_DATA;

    return result;
}

int main(int argc, char* argv[])
{
    int rc = OK;
    float average;
    FILE *f;

    if (argc == 2)
    {
        f = fopen(argv[1], "r");
        if (f == NULL)
        {
            rc = ERR_DATA;
            printf("File is empty or does not exist!");
        }
        else
        {
            average = finding_average(f, &rc);
            if (rc == ERR_DATA)
            {
                printf("There are no positive numbers in file!");
            }
            else
            {
                printf("Result: %f", average);
            }
        }
        fclose(f);
    }
    else
    {
        rc = WRONG_CMD;
        printf("Wrong parametrs! It must be like: \"app.exe file_name.txt\"");
    }

    return rc;
}
