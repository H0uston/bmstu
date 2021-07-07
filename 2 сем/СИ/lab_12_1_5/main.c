#if TYPE != 3
#include "function.h"
#else
#include <dlfcn.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR_FILE (-1)
#define ERR_MEMORY (-2)
#define ERR_EMPTY (-3)
#define ERR_CMD (-5)
#define ERR_LIB (-6)
#define ERR_FUNC (-7)
typedef int (*sort_compare_int)(const void *, const void *);
typedef int (*io_read)(FILE *, int **, int **, int *);
typedef int (*filter_sum)(const int *, const int *);
typedef int (*filter_count)(const int *, const int *, int);
typedef int (*key)(const int *, const int *, int *, int *);
typedef void (*mysort)(void *, size_t, size_t, int (*compare)(const void*, const void*));
typedef void (*io_array_fprintf)(FILE *, const int *, const int *);
#endif

int main(int argc, char **argv)
{
    int rc = OK;
    setbuf(stdout, NULL);
#if TYPE == 3
    sort_compare_int func_sort_compare_int = NULL;
    io_read func_io_read = NULL;
    filter_sum func_filter_sum = NULL;
    filter_count func_filter_count = NULL;
    key func_key = NULL;
    mysort func_mysort = NULL;
    io_array_fprintf func_io_array_fprintf = NULL;

    void *library;
    library = dlopen("libfunc.so", RTLD_LAZY);
    if (!library)
    {
        printf("Problems with opening library.\n");
        rc = ERR_LIB;
    }

    func_sort_compare_int = dlsym(library, "sort_compare_int");
    if (!func_sort_compare_int)
    {
        printf("fsci Can not load function.\n");
        rc = ERR_FUNC;
    }

    func_io_read = dlsym(library, "io_read");
    if (!func_io_read)
    {
        printf("ir Can not load function.\n");
        rc = ERR_FUNC;
    }

    func_filter_sum = dlsym(library, "filter_sum");
    if (!func_filter_sum)
    {
        printf("fs Can not load function.\n");
        rc = ERR_FUNC;
    }

    func_filter_count = dlsym(library, "filter_count");
    if (!func_filter_count)
    {
        printf("Can not load function.\n");
        rc = ERR_FUNC;
    }

    func_key = dlsym(library, "key");
    if (!func_key)
    {
        printf("Can not load function.\n");
        rc = ERR_FUNC;
    }

    func_mysort = dlsym(library, "mysort");
    if (!func_mysort)
    {
        printf("Can not load function.\n");
        rc = ERR_FUNC;
    }

    func_io_array_fprintf = dlsym(library, "io_array_fprintf");
    if (!func_io_array_fprintf)
    {
        printf("Can not load function.\n");
        rc = ERR_FUNC;
    }
#endif
    int count = 0;
    int *array = NULL;
    int *array_end = NULL;
    bool filter_status = false;

    FILE *file_in;
    FILE *file_out;

    if (argc < 3 || argc > 4)
    {
        rc = ERR_CMD;
        printf("Wrong CMD. app.exe file_in.txt file_out.txt [f]");
    }

    if (rc == OK)
    {
        file_in = fopen(argv[1], "r");

        if (file_in == NULL)
        {
            rc = ERR_FILE;
            printf("Problems with input data file.");
        }
    }

    if (rc == OK && argc == 4 && strcmp(argv[3], "f") == 0)
    {
        filter_status = true;
    }
    else if (rc == OK && argc == 4 && strcmp(argv[3], "f") != 0)
    {
        printf("Wrong CMD. app.exe file_in.txt file_out.txt [f]");
        rc = ERR_CMD;
        fclose(file_in);
    }

    if (rc == OK)
    {
#if TYPE != 3
        rc = io_read(file_in, &array, &array_end, &count);
#else
        rc = (*func_io_read)(file_in, &array, &array_end, &count);
#endif
        fclose(file_in);
        if (rc != OK)
        {
            if (rc == ERR_EMPTY)
                printf("Data file is empty or has wrong data.");
            else if (rc == ERR_MEMORY)
                printf("Problems with computer memory.");
            else
                printf("Unknown error.");
        }
    }

    if (rc == OK)
    {
        int *array_filtered = NULL;
        int *array_filtered_end = NULL;

        if (filter_status)
        {
            int sum = 0;
#if TYPE != 3
            sum = filter_sum(array, array_end);
            int count = filter_count(array, array_end, sum);
#else
            sum = (*func_filter_sum)(array, array_end);
            int count = (*func_filter_count)(array, array_end, sum);
#endif
            if (count >= 1)
            {
                array_filtered = malloc(count * sizeof(int));
                if (!array_filtered)
                    return ERR_MEMORY;
                else
                {
                    array_filtered_end = array_filtered + count;
#if TYPE != 3
                    rc = key(array, array_end, array_filtered, array_filtered_end);
#else
                    rc = (*func_key)(array, array_end, array_filtered, array_filtered_end);
#endif
                }

            }
            else
            {
                array_filtered = array;
                array_filtered_end = array_end;
            }
        }
        else
        {
            array_filtered = array;
            array_filtered_end = array_end;
        }

        if (rc == OK)
        {
#if TYPE != 3
            mysort(array_filtered, array_filtered_end - array_filtered, sizeof(int), sort_compare_int);
#else
            (*func_mysort)(array_filtered, array_filtered_end - array_filtered, sizeof(int), func_sort_compare_int);
#endif
            file_out = fopen(argv[2], "w");
            if (file_out == NULL)
            {
                rc = ERR_FILE;
                printf("Problems with output data file");
            }
            else
            {
#if TYPE != 3
                io_array_fprintf(file_out, array_filtered, array_filtered_end);
#else
                (*func_io_array_fprintf)(file_out, array_filtered, array_filtered_end);
#endif
                fclose(file_out);
            }
        }
        else
        {
            if (rc == ERR_EMPTY)
                printf("Data file is empty or have wrong data.");
            else if (rc == ERR_MEMORY)
                printf("Problems with computer memory.");
            else
                printf("Unknown error.");
        }

        if (!filter_status)
            free(array);
        else if (array != NULL && array_filtered == NULL)
            free(array);
        else if (rc != ERR_MEMORY)
        {
            free(array);
            free(array_filtered);
        }
    }

#if TYPE == 3
    if (rc != ERR_LIB)
        dlclose(library);
#endif

    return rc;
}