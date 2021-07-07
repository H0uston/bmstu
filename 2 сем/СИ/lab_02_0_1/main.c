#include <stdio.h>
#include <math.h>
#define OK 0
#define ERR_TP 1
#define ERR_RANGE 2

int exponentiation(int base, int power)
{
    int result, i;

    i = 1;
    result = 1;
    while (i <= power)
    {
        result *= base;
        i += 1;
    }

    return result;
}

int main(void)
{
    int base, power, rc = OK;

    printf("Enter integer number: \n");
    if (scanf("%d", &base) == 1)
    {
        printf("Enter positive integer number: \n");
        if (scanf("%d", &power) == 1)
        {
            if (power > 0)
            {
                printf("Result: %d", exponentiation(base, power));
            }
            else
            {
                printf("Power must be positive!\n");
                rc = ERR_RANGE;
            }
        }
        else
        {
            printf("Power must be integer!\n");
            rc = ERR_TP;
        }
    }
    else
    {
        printf("Base must be integer!\n");
        rc = ERR_TP;
    }

    return rc;
}
