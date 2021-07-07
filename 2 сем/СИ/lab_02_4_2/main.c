#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define OK 0
#define ERR_TP 1
#define ERR_RANGE 2
#define EPS 0.000001

int checking_point(float x1, float x2, float x, float y1, float y2, float y)
{
    if (((x - x1) * (y2 - y1) - (x2 - x1) * (y - y1) < EPS) &&
        (((((x1 < x) || (fabs(x - x1) < EPS)) && ((x < x2) || (fabs(x2 - x) < EPS))) &&
        (((y1 < y) || (fabs(y - y1) < EPS)) && ((y < y2) || (fabs(y2 - y) < EPS)))) ||
        ((((x1 > x) || (fabs(x1 - x) < EPS)) && ((x > x2) || (fabs(x - x2) < EPS))) &&
        (((y1 > y) || (fabs(y1 - y) < EPS)) && ((y > y2) || (fabs(y - y2) < EPS))))))
        return true;
    else
        return false;
}

int main(void)
{
    float coord_x1, coord_x2, coord_x3, coord_y1, coord_y2, coord_y3;
    int rc = OK;
    printf("Enter coordinates of start point: ");
    if (scanf("%f%f", &coord_x1, &coord_y1) == 2)
    {
        printf("Enter coordinates of end point: ");
        if (scanf("%f%f", &coord_x2, &coord_y2) == 2)
        {
            if ((coord_x1 != coord_x2) || (coord_y1 != coord_y2))
            {
                printf("Enter coordinates of point: ");
                if (scanf("%f%f", &coord_x3, &coord_y3) == 2)
                {
                    if (checking_point(coord_x1, coord_x2, coord_x3, coord_y1, coord_y2, coord_y3))
                        printf("The point belongs to segment 1");
                    else
                        printf("The point does not belongs to segment 0");
                }
                else
                {
                    printf("Invalid coordinates of point!");
                    rc = ERR_TP;
                }
            }
            else
            {
                printf("Coordinates must not be the same!");
                rc = ERR_RANGE;
            }
        }
        else
        {
            printf("Invalid coordinates of point!");
            rc = ERR_TP;
        }
    }
    else
    {
        printf("Invalid coordinates of point!");
        rc = ERR_TP;
    }
    return rc;
}
