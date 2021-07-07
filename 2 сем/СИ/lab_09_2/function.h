#ifndef LAB_09_2_FUNCTION_H
#define LAB_09_2_FUNCTION_H

#include "config.h"
#include "error.h"
#include "my_string.h"

ssize_t my_getline(char **result, size_t *buffer_size, FILE *file);

char *str_replace(const char *source, const char *search, const char *replace);

#endif //LAB_09_2_FUNCTION_H
