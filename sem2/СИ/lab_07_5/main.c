/**
Функция сортировки массива.
*/
#include "config.h"
#include "array_io.h"
#include "error.h"
#include "filter.h"
#include "sort.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    int count = 0;
    int *array = NULL;
    int *array_end = NULL;
    bool filter_status = false;

    int rc = OK;

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
        rc = io_read(file_in, &array, &array_end, &count);
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
            rc = key(array, array_end, &array_filtered, &array_filtered_end);
        else
        {
            array_filtered = array;
            array_filtered_end = array_end;
        }

        if (rc == OK)
        {
            mysort(array_filtered, array_filtered_end - array_filtered, sizeof(int), sort_compare_int);
            file_out = fopen(argv[2], "w");
            if (file_out == NULL)
            {
                rc = ERR_FILE;
                printf("Problems with output data file");
            }
            else
            {
                io_array_fprintf(file_out, array_filtered, array_filtered_end);
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

    return rc;
}
