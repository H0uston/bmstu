#include <stdio.h>
#include <math.h>
#define OK 0
#define ERR_TP 1
#define ERR_RANGE 2

float f_func(float x)
{
    float result;

    result = pow((1 + x), -3);

    return result;
}

float s_func(float x, float eps)
{
    float sum = 0, member_of_series = 1, numerator = 1;
    int i = 1;

    while (fabs(member_of_series) > eps)
    {
        sum += member_of_series;
        numerator *= (-1) * x;
        member_of_series = (numerator * (i + 1) * (i + 2)) / 2;
        i += 1;
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
        if (fabs(x) < 1)
        {
            printf("Enter eps: ");
            if (scanf("%f", &eps) == 1)
            {
                if (0 < eps && eps < 1)
                {
                    f_result = f_func(x);
                    s_result = s_func(x, eps);

                    abs_result = fabs(f_result - s_result);
                    rel_result = fabs((f_result - s_result) / f_result);
                    // printf("%.8f%.8f%.8f%.8f", s_result, f_result, abs_result, rel_result);
                    printf("Results: \nApproximation of s(x) = %8.8f \n", s_result);
                    printf("Exact value of f(x) = %8.8f \n", f_result);
                    printf("Absolute error = %8.8f \n", abs_result);
                    printf("Relative error = %8.8f \n", rel_result);
                }
                else
                {
                    rc = ERR_RANGE;
                    printf("Eps must me positive, but less than one!");
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
            rc = ERR_RANGE;
            printf("x must be modulo less than one");
        }
    }
    else
    {
        rc = ERR_TP;
        printf("Wrong x!");
    }

    return rc;
}
