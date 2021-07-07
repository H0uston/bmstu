#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <math.h>
#define N 10
#define EPS 0.000001

void arr_print(const float a[], int n);
int arr_input(FILE *f, float a[], int *n);
void process(float *a, int n, float border);

#endif // CONFIG_H
