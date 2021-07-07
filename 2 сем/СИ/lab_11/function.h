//
// Created by Houston on 18/11/2018.
//

#ifndef LAB_11_FUNCTION_H
#define LAB_11_FUNCTION_H

#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#define OCTAL_BASE 8
#define DECIMAL_BASE 10

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...);

size_t len(const char *str);

size_t int_len(long int number, int base);

void make_octal(char *result, unsigned int num);

char *my_strncpy(char *str, const char *buf, int end_index);

void printf_number(char *s, long int number, int n);

#endif //LAB_11_FUNCTION_H
