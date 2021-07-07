#ifndef ORGANIZE_H
#define ORGANIZE_H

#include "config.h"
#include "io.h"
#include "error.h"
#include "function.h"

int organize_invertible(const char *file_name_a, const char *file_name_b);

int organize_sum(const char *file_name_a, const char *file_name_b, const char *file_name_c);

int organize_mult(const char *file_name_a, const char *file_name_b, const char *file_name_c);

void organize_info(void);

#endif // ORGANIZE_H
