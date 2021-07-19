#include "function.h"

int read_data(FILE *file, char **result, size_t *result_size, size_t *count_row)
{
    size_t buffer_size = BUFFER_SIZE;
    size_t size_str = 0;
    char *tmp = NULL;
    char *buffer = NULL;
    char *string = NULL;
    tmp = realloc(tmp, (buffer_size + 1) * sizeof(char));
    if (tmp == NULL)
        return ERR_MEMORY;
    buffer = tmp;
    while (fgets(buffer, buffer_size, file) != NULL)
    {
        size_t readed = strlen(buffer);
        tmp = realloc(tmp, (readed + size_str + 1) * sizeof(char));
        if (tmp == NULL)
            return ERR_MEMORY;
        string = tmp;
        strcpy(string + size_str, buffer);
        size_str += readed;
        if (string[readed - 1] == '\n')
            (*count_row) += 1;
    }

    if (size_str == 0)
        return ERR_EMPTY;

    *result = string;
    *result_size = size_str;
    *count_row += 1;

    return OK;
}
/*
int find_count_column(const char *string, const size_t count_row, size_t *count_column)
{
    size_t size_str = strlen(string);
    bool prev = false;
    size_t general_count_column;
    for (int i = 0; i < size_str && strcmp(string[i], '\n') != 0; i++, prev = false)
    {
        if (i == 0 && strcmp(string[i], " ") != 0)
            prev = true;
        else if ((strcmp(string[i], " ") == 0) && prev == true)
        {
            general_count_column += 1;
            prev = false;
        }
        else if (i == size_str - 1 && prev == true)
            general_count_column += 1;
        else
            prev = true;
    }

    size_t local_count_column = 0;
    for (int i = 0; i < size_str; i++)
    {
        if (i == 0 && strcmp(string[i], " ") != 0)
            prev = true;
        else if (strcmp(string[i], "\n") == 0)
        {
            if (prev)
                local_count_column += 1;

            if (local_count_column == general_count_column)
                continue;
            else
            {
                return ERR_SIZE;
            }
        }
        else if ((strcmp(string[i], " ") == 0) && prev == true)
        {
            local_count_column += 1;
            prev = false;
        }
        else if (i == size_str - 1 && prev == true)
            local_count_column += 1;
        else
            prev = true;
    }

    *count_column = general_count_column;
    return OK;
}
*/
