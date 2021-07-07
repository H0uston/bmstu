/* Поместить в новый массив все элементы исходного,
 * которые больше среднего арифметического его элементов */
#include <stdio.h>
#define N 10
#define OK 0
#define ERR_RANGE 1
#define ERR_TP 2
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

float finding_average(const int *arr, int n)
{
    float sum = 0, average;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    average = sum / n;
    return average;
}

void forming_new_array(const int *arr, int *num, int n, int *k, float average)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > average)
        {
            num[*k] = arr[i];
            (*k)++;
        }
    }
}

int main(void)
{
    int arr[N], num[N], rc = OK, n, k = 0;
    float average;

    rc = input(arr, &n);
    if (rc == OK)
    {
        // print(arr, n);
        average = finding_average(arr, n);
        forming_new_array(arr, num, n, &k, average);
        if (k == 0)
        {
            printf("New array is empty.");
            rc = ERR_VLE;
        }
        else
        {
            printf("New array: ");
            print(num, k);
        }
    }
    else if (rc == ERR_RANGE)
        printf("Wrong range of size's value!");
    else if (rc == ERR_TP)
        printf("Wrong value of element!");

    return rc;
}
