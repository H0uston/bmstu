/*
Даны основания и высота равнобедренной трапеции. Найти периметр трапеции.
*/
#include <stdio.h>
#include <math.h>
#define TEXT "Perimetr is %f"
int main(void)
{
    float basis_a, basis_b, height, half_module_diff, lateral_side, perimetr;

    printf("Enter a: "); // вводится значение первого основания
    scanf("%f", &basis_a);

    printf("Enter b: "); // вводится значение второго основания
    scanf("%f", &basis_b);

    printf("Enter h: "); // вводится значение высоты трапеции
    scanf("%f", &height);

    half_module_diff = (sqrt(pow(basis_a - basis_b, 2))) / 2;
    lateral_side = sqrt(height * height + half_module_diff * half_module_diff);
    perimetr = 2 * lateral_side + basis_a + basis_b;

    printf(TEXT, perimetr);

    return 0;
}
