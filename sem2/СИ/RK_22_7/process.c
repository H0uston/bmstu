#include "config.h"

void process(float *a, int n, float border)
{
    int left = 0, right = n - 1, temp;

    while (left < right)
    {
        if (a[left] < border)
            left += 1;
        else if (a[right] >= border)
                right -= 1;
        else
        {
            temp = a[left];
            a[left] = a[right];
            a[right] = temp;
            left += 1;
            right -= 1;
        }
    }
}
