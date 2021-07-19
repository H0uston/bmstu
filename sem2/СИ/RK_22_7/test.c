#include "config.h"
#include <stdbool.h>

bool is_equal(float *a, int n, float *b)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return false;
    }

    return true;
}

void test_process(void)
{
    float a[] = {5, 6, 3, 4, 2, 7, 1};
    float border_a = 5;
    int n_a = 7;
    float res_a[] = {1, 2, 3, 4, 6, 7, 5};

    float b[] = {2, 4, 1, 9, 10};
    float border_b = 1;
    int n_b = 5;
    float res_b[] = {1, 4, 2, 9, 10};

    float c[] = {21, -16, -2.5, 1, 18};
    float border_c = 0;
    int n_c = 5;
    float res_c[] = {-2.5, -16, 21, 1, 18};

    {
        process(a, n_a, border_a);
        printf("TEST1: ");
        if (is_equal(a, n_a, res_a))
            printf("PASSED\n");
        else
            printf("FAILED\n");
    }
    {
        process(b, n_b, border_b);
        printf("TEST2: ");
        if (is_equal(b, n_b, res_b))
            printf("PASSED\n");
        else
            printf("FAILED\n");
    }
    {
        process(c, n_c, border_c);
        printf("TEST3: ");
        if (is_equal(c, n_c, res_c))
            printf("PASSED\n");
        else
            printf("FAILED\n");
    }

}

int main(void)
{
    test_process();

    return 0;
}
