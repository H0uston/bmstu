#include <stdio.h>
#define OK 0
#define ERR_TP 1
#define ERR_RANGE 2
#define ERR_ZERO 3

int func(int num, int a, int b, int *rc)
{
    int result = 0, i = 1, rem, count = 0;

    while (num > 0)
    {
        count += 1;
        rem = num % 10;
        if (rem != a && rem != b)
        {
            result += rem * i;
            i *= 10;
        }
        else
            count -= 1;
        num /= 10;
    }

    if (count == 0)
        *rc = ERR_ZERO;

    return result;
}

int main(void)
{
    int num, a, b, result, rc = OK;

    printf("Enter integer positive number: ");
    if (scanf("%d", &num) == 1)
    {
        if (num > 0)
        {
            printf("Enter digits a and b: ");
            if (scanf("%d%d", &a, &b) == 2)
            {
                if ((a >= 0 && a < 10) && (b >= 0 && b < 10))
                {
                    result = func(num, a, b, &rc);
                    if (rc == ERR_ZERO)
                    {
                        printf("There are no digits in your number!");
                    }
                    else
                        printf("Result: %d", result);
                }
                else
                {
                    printf("a and b must be digits!");
                    rc = ERR_TP;
                }
            }
            else
            {
                printf("Wrong numbers!");
                rc = ERR_TP;
            }
        }
        else
        {
            printf("Number must me positive!");
            rc = ERR_RANGE;
        }
    }
    else
    {
        printf("Wrong number!");
        rc = ERR_TP;
    }

    return rc;
}
