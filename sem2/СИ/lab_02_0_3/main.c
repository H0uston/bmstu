#include <stdio.h>
#include <math.h>
#define OK 0
#define ERR_TP 1
#define ERR_RANGE 2

float f_func(float x)
{
    float result;

    result = exp(x);

    return result;
}

float s_func(float x, float eps)
{
    float sum = 1, member_of_series = 1;
    int denominator = 1;

    while (fabs(member_of_series) > eps)
    {
        member_of_series *= x / denominator;
        sum += member_of_series;
        denominator++;
    }

    return sum;
}

int main(void)
{
    float eps, x, f_result, s_result, abs_result, rel_result;
    int rc = OK;

    printf("Enter x: ");
    if (scanf("%f", &x) == 1)
    {
        printf("Enter eps: ");
        if (scanf("%f", &eps) == 1)
        {
            if (0 < eps && eps < 1)
            {
                f_result = f_func(x);
                s_result = s_func(x, eps);

                abs_result = fabs(f_result - s_result);
                rel_result = fabs(abs_result / f_result);
                printf("Results:\nApproximation of s(x) = %.6f\n", s_result);
                printf("Exact value of f(x) = %.6f \n", f_result);
                printf("Absolute error = %.6f \n", abs_result);
                printf("Relative error = %.6f \n", rel_result);
            }
            else
            {
                rc = ERR_RANGE;
                printf("Eps must be in interval positive, but less than one!");
            }
        }
        else
        {
            rc = ERR_TP;
            printf("Wrong eps!");
        }
    }
    else
    {
        rc = ERR_TP;
        printf("Wrong x!");
    }

    return rc;
}
