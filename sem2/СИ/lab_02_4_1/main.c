#include <stdio.h>
#define OK 0
#define ERR_TP 1
#define ERR_RANGE 2

void find_factors(int number)
{
    int factor = 2;
    while (factor <= number)
    {
        if (number % factor == 0)
        {
            printf("%d", factor);
            number = number / factor;
            if (number > 1)
            {
                printf(" ");
            }
        }
        else
            factor = factor + 1;
    }
}

int main(void)
{
    int number, rc = OK;

    printf("Enter number: ");
    if (scanf("%d", &number) == 1)
    {
        if (number > 0)
        {
            find_factors(number);
        }
        else
        {
            printf("Number must be positive!");
            rc = ERR_RANGE;
        }
    }
    else
    {
        printf("Number must be integer!");
        rc = ERR_TP;
    }

    return rc;
}
