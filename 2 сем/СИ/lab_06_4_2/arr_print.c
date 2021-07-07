#include <stdio.h>
#include "arr_print.h"

void arr_print(const int *pbeg, const int *pend)
{
    printf("Array: \n");
    while (pbeg < pend)
    {
        printf("%d ", *pbeg);
        pbeg++;
    }
    printf("\n");
}
