//
// Created by Houston on 21/10/2018.
//
#ifndef LAB_09_2_STRING_H
#define LAB_09_2_STRING_H

#include "config.h"

size_t len(const char *str);

char *str_copy_n(char *str, const char *buf, int end_index);

char *find(const char *string, const char *substring);

int str_compare(const char *str_a, const char *str_b);

char *my_strcpy(char *str, const char *buf);

void str_fprintf(FILE *file, const char *str, int size);

#endif //LAB_09_2_STRING_H
