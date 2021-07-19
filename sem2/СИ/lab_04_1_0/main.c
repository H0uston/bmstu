/* Подсчитать сумму чётных элементов массива */
#include <stdio.h>
#define N 10
#define OK 0
#define ERR_TP 1
#define ERR_RANGE 2
#define ERR_VLE 3

int input(int *arr, int *n)
{
    int i = 0, rc = OK;
    printf("Enter size of array: \n");
    if (scanf("%d", n) != 1)
    {
        rc = ERR_TP;
    }
    else
    {
        if (*n > 0 && *n <= N)
        {
            printf("Enter integer numbers: ");
            for (i = 0; i < *n; i++)
            {
                if (scanf("%d", &arr[i]) != 1)
                {
                    rc = ERR_TP;
                    break;
                }
            }
        }
        else
        {
            rc = ERR_RANGE;
        }
    }
    return rc;
}

void print(const int *arr, int n)
{
    printf("\nArray: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int process(const int *arr, int n, int *rc)
{
    int sum = 0, count = 0;
    for (int i = 0; i < n; i++)
        if ((arr[i] % 2) == 0)
        {
            count += 1;
            sum += arr[i];
        }
    if (count == 0)
    {
        *rc = ERR_VLE;
    }
    return sum;
}

int main(void)
{
    int arr[N], n, sum = 0, rc = OK;

    rc = input(arr, &n);
    if (rc == OK)
    {
        // print(arr, n);
        sum = process(arr, n, &rc);
        if (rc == OK)
            printf("Sum: %d", sum);
        else
            printf("There are no even numbers in array!");
    }
    else if (rc == ERR_RANGE)
        printf("Wrong range of size's value!");
    else if (rc == ERR_TP)
        printf("Wrong value of element!");

    return rc;
}

