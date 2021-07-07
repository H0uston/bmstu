/* Программа вычисляет нормальный вес и индекс веса человека */
#include <stdio.h>

int main(void)
{
    float normal_weight, index_weight, sm_height, m_height, mass, length_of_rib_cage;
    printf("Enter height of person (in sm): ");
    scanf("%f", &sm_height);
    m_height = sm_height / 100;
    printf("Enter length of rib cage(in sm): ");
    scanf("%f", &length_of_rib_cage);
    printf("Enter weight of person(in kg): ");
    scanf("%f", &mass);

    normal_weight = sm_height * length_of_rib_cage / 240;
    index_weight = mass / (m_height * m_height);

    printf("Normal weight: %f\n", normal_weight);
    printf("Index of weight: %f\n", index_weight);

    return 0;
}
