/* Сортировка пузырьком c флагом*/
#include <stdio.h>
#include <stdbool.h>
#define N 10
#define OK 0
#define ERR_RANGE 1
#define ERR_TP 2

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

void sorted(int *arr, int n)
{
    int per, i = 0, j, flag = true;
    while (flag == true)
    {
        flag = false;
        for (j = 0; j < (n - 1 - i); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                per = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = per;
                flag = true;
            }
        }
        i++;
    }
}

int main(void)
{
    int arr[N], n, rc = OK;
    rc = input(arr, &n);
    if (rc == OK)
    {
        // print(arr, n);
        sorted(arr, n);
        printf("Sorted array: ");
        print(arr, n);
    }
    else if (rc == ERR_RANGE)
        printf("Wrong range of size's value!");
    else if (rc == ERR_TP)
        printf("Wrong value of element!");
    return rc;
}
