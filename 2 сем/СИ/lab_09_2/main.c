#include "config.h"

int main(int args, char **argv)
{
    int status = OK;
    setbuf(stdout, NULL);
    FILE *file_in, *file_out;
    char *result = NULL;
    if (args != 7 || !str_compare(argv[3], "-s") || !str_compare(argv[5], "-r"))
        status = ERR_CMD;

    if (status == OK)
    {
        file_in = fopen(argv[1], "r");
        if (file_in == NULL)
            status = ERR_FILE;
        else
        {
            fseek(file_in, 0, SEEK_END);
            long pos = ftell(file_in);
            if (pos == 0)
                status = ERR_FILE;
            else
                rewind(file_in);
        }
    }

    if (status == OK)
    {
        file_out = fopen(argv[2], "w");
        if (file_out == NULL)
        {
            status = ERR_FILE;
            fclose(file_in);
        }
    }

    if (status == OK)
    {
        size_t buffer_size = 0; // По условию задачи
        ssize_t size = 0;
        char *buffer = NULL;
        while ((size = my_getline(&buffer, &buffer_size, file_in)) != NONE)
        {
            result = str_replace(buffer, argv[4], argv[6]);
            fprintf(file_out, "%s", result);
            if (buffer != NULL)
                free(buffer);
            buffer = NULL;
            if (result != NULL)
                free(result);
        }
        if (buffer != NULL)
            free(buffer);
        fclose(file_in);
        fclose(file_out);
    }

    switch (status)
    {
        case OK:
            // printf("\nProgram has successfully completed.");
            break;
        case ERR_FILE:
            printf("\nProblems with file.");
            break;
        case ERR_CMD:
            printf("\nWrong CMD. ./app.exe in.txt out.txt -s search -r replace");
            break;
        case ERR_MEMORY:
            printf("\nProblems with memory.");
            break;
    }


    return status;
}

