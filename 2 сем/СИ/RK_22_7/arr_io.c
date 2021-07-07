#include "errors.h"
#include "config.h"

int arr_input(FILE *f, float a[], int *n)
{
    int i, rc = OK;
    if (fscanf(f, "%d", n) == 1)
    {
        if (*n > 0 && *n < N)
        {
            while (fscanf(f, "%f", &a[i]) == 1 && i < *n)
                i++;
            if (i != *n)
                rc = ERR_CNT;
        }
        else
            rc = ERR_RANGE;
    }
    else
        rc = ERR_RANGE;

    return rc;
}

void arr_print(const float a[], int n)
{
    printf("Array: \n");
    for (int i = 0; i < n; i++)
        printf("%.3f ", a[i]);
    printf("\n");
}
