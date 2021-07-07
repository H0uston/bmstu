#include <stdio.h>
#define N 100

void arr_input(FILE *f, int *pbeg, int **pend)
{
    int count = 0;
    int *pv = pbeg;
    while (fscanf(f, "%d ", pbeg) == 1 && count < N)
    {
        pbeg++;
        count++;
    }
    *pend = pv + count;
}
