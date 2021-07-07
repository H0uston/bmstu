/*
Вычисляет площадь круга
*/

#include <stdio.h>
#define PI 3.14

float square_of_sercule_func(float radius)
{
    float square_of_sercule;
    square_of_sercule = PI * radius * radius;

    return square_of_sercule;
}

float square_of_rectangle_func(float basis_a, float basis_b)
{
    float square_of_rectangle;
    square_of_rectangle = basis_a * basis_b;

    return square_of_rectangle;
}

int main(void)
{
    float square_of_rectangle, square_of_sercule, square_of_figures, basis_a, basis_b, radius;

    printf("Input basis a and basis b: ");
    scanf("%f%f", &basis_a,&basis_b);
    printf("Input radius: ");
    scanf("%f",&radius);

    square_of_rectangle = square_of_rectangle_func(basis_a, basis_b);
    square_of_sercule = square_of_sercule_func(radius);
    square_of_figures = square_of_rectangle + square_of_sercule;

    printf("Square of rectangle is %8.3f\n", square_of_rectangle);
    printf("Square of sercule is %8.3f\n", square_of_sercule);
    printf("Sum of both figures %8.3f\n", square_of_figures);
    return 0;
}
