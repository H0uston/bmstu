/* Удалите из исходного массива все элементы,
 * которые являются числами-палиндромами.*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define N 10
#define OK 0
#define ERR_RANGE 1
#define ERR_TP 2
#define BASE 10

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

int is_pallendroid(int num)
{
    int per, new_num;
    if (num >= 0)
    {
        per = num;
        new_num = 0;
        while (per != 0)
        {
            new_num = new_num * BASE + (per % BASE);
            per /= BASE;
        }
        if (num == new_num)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}


void delete_palindrome(int *arr, int *n, int *i)
{
    for (int j = *i; j < (*n - 1); j++)
        arr[j] = arr[j + 1];
    (*n)--;
    (*i)--;
}

void find_palindrome(int *arr, int *n)
{
    for (int i = 0; i < *n; i++)
        if (is_pallendroid(arr[i]) == true)
            delete_palindrome(arr, n, &i);
}

int main(void)
{
    int arr[N], rc = OK, n;

    rc = input(arr, &n);
    if (rc == OK)
    {
        // print(arr, n);
        find_palindrome(arr, &n);
        if (n == 0)
            printf("There are no elements in array.");
        else
        {
            printf("Array without pallendroids: ");
            print(arr, n);
        }
    }
    else if (rc == ERR_RANGE)
        printf("Wrong range of size's value!");
    else if (rc == ERR_TP)
        printf("Wrong value of element!");


    return rc;
}

