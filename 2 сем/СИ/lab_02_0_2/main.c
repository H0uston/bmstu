#include <stdio.h>
#include <math.h>
#define OK 0
#define ERR_TP 1
#define ERR_WRONG_INPUT 2
#define NONTRIANGLE -1
#define SHARP 0
#define STRAIGHT 1
#define OBTUSE 2
#define EPS 0.000001

float length(float x1, float y1, float x2, float y2)
{
    float length;

    length = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

    return length;
}

int check(float first_edge, float second_edge, float third_edge)
{
    if (first_edge >= second_edge + third_edge ||
        second_edge >= first_edge + third_edge ||
        third_edge >= second_edge + first_edge)
    {
        return NONTRIANGLE;
    }
    else if (fabs(pow(first_edge, 2) - (pow(second_edge, 2) + pow(third_edge, 2))) < EPS ||
        fabs(pow(second_edge, 2) - (pow(first_edge, 2) + pow(third_edge, 2))) < EPS ||
        fabs(pow(third_edge, 2) - (pow(second_edge, 2) + pow(first_edge, 2))) < EPS)
    {
        return STRAIGHT;
    }
    else if ((pow(first_edge, 2) > (pow(second_edge, 2) + pow(third_edge, 2))) ||
        (pow(second_edge, 2) > (pow(first_edge, 2) + pow(third_edge, 2))) ||
        (pow(third_edge, 2) > (pow(second_edge, 2) + pow(first_edge, 2))))
    {
        return OBTUSE;
    }
    else
    {
        return SHARP;
    }
}

int main(void)
{
    float coord_x1, coord_x2, coord_x3, coord_y1, coord_y2, coord_y3;
    float first_edge, second_edge, third_edge;
    int result, rc = OK;

    printf("Enter first point (x, y), second point (x, y), third point (x, y): \n");
    if (scanf("%f%f%f%f%f%f", &coord_x1, &coord_y1, &coord_x2, &coord_y2, &coord_x3, &coord_y3) == 6)
    {
        first_edge = length(coord_x1, coord_y1, coord_x2, coord_y2);
        second_edge = length(coord_x2, coord_y2, coord_x3, coord_y3);
        third_edge = length(coord_x1, coord_y1, coord_x3, coord_y3);

        result = check(first_edge, second_edge, third_edge);

        if (result == NONTRIANGLE)
        {
            printf("Triangle does not exist!");
            rc = ERR_WRONG_INPUT;
        }
        else if (result == SHARP)
            printf("Angle is sharp 0");
        else if (result == STRAIGHT)
            printf("Angle is straight 1");
        else
            printf("Angle is obtuse 2");
    }
    else
    {
        printf("Invalid values of coordinates!");
        rc = ERR_TP;
    }

    return rc;
}
