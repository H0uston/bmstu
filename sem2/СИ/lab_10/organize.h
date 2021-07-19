#ifndef __LAB_10_ORGANIZE_H__
#define __LAB_10_ORGANIZE_H__

#include "config.h"

int organize_find(const char *file_name_in, const char *file_name_out, const char *string);

int organize_pop_back(const char *file_name_in, const char *file_name_out);

int organize_append(const char *file_name_in_a, const char *file_name_in_b, const char *file_name_out);

int organize_sort(const char *file_name_in, const char *file_name_out);

void organize_info(void);

#endif //LAB_10_ORGANIZE_H
