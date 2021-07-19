#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define OK 0
#define ERR_DATA 1
#define ERR_WRONG_CMD 2
#define ERR_FILE 3
#define NUMBERS_IN_FILE 10
#define MAX_RANDOM_NUMBER 100

int create_file(FILE *f)
{
    int num, i, count = 0;
    for (i = 0; i < NUMBERS_IN_FILE; i++)
    {
        num = rand() % MAX_RANDOM_NUMBER;
        if (fwrite(&num, sizeof(int), 1, f) == true)
            count += 1;
    }
    if (count != NUMBERS_IN_FILE)
        return ERR_FILE;
    else
        return OK;
}

int print_file(FILE *f)
{
    int num, i, count = 0, length;
    if (fseek(f, 0, SEEK_END) != false)
        return ERR_DATA;
    length = ftell(f) / sizeof(int);
    if (fseek(f, 0, SEEK_SET) != false)
        return ERR_DATA;
    for (i = 0; i < length; i++)
    {
        if (fread(&num, sizeof(int), 1, f) == true)
        {
            printf("%d ", num);
            count += 1;
        }
        else
            return ERR_DATA;
    }
    return OK;
}

int get_number_pos(FILE *f, int step, int *num)
{
    if (fseek(f, step, SEEK_SET) == false)
        if (fread(num, sizeof(int), 1, f) == true)
            return OK;
        else
            return ERR_DATA;
    else
        return ERR_DATA;
}

int put_number_by_pos(FILE *f, int step, int num)
{
    if (fseek(f, step, SEEK_SET) == false)
        if (fwrite(&num, sizeof(int), 1, f) == true)
            return OK;
        else
            return ERR_DATA;
    else
        return ERR_DATA;
}

int sort_file(FILE *f)
{
    int num, next_num, i, j, step = 0, rc, length;
    if (fseek(f, 0, SEEK_END) != false)
        return ERR_DATA;
    length = ftell(f) / sizeof(int);
    if (fseek(f, 0, SEEK_SET) != false)
        return ERR_DATA;
    for (i = 0; i < (length - 1); i++)
    {
        for (j = 0; j < (length - 1); j++)
        {
            rc = get_number_pos(f, step, &num);
            if (rc != OK)
                return rc;
            step += sizeof(int);
            rc = get_number_pos(f, step, &next_num);
            if (rc != OK)
                return rc;
            if (num > next_num)
            {
                step -= sizeof(int);
                rc = put_number_by_pos(f, step, next_num);
                if (rc != OK)
                    return ERR_DATA;
                step += sizeof(int);
                rc = put_number_by_pos(f, step, num);
                if (rc != OK)
                    return ERR_DATA;
            }
        }
        step = 0;
    }
    return rc;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    FILE *f;
    int rc = OK;
    if (argc == 3)
    {
        if (strcmp(argv[1], "c") == 0)
        {
            f = fopen(argv[2], "wb");
            rc = create_file(f);
            if (rc != OK)
                printf("Problmes with file!");
            else
                printf("File was created.");
            fclose(f);
        }
        else if (strcmp(argv[1], "p") == 0)
        {
            f = fopen(argv[2], "rb");
            if (f != NULL)
            {
                rc = print_file(f);
                if (rc != OK)
                    printf("Problems with data!");
                fclose(f);
            }
            else
            {
                rc = ERR_FILE;
                printf("File is not created!");
            }
        }
        else if (strcmp(argv[1], "s") == 0)
        {
            f = fopen(argv[2], "rb + wb");
            if (f != NULL)
            {
                rc = sort_file(f);
                if (rc != OK)
                    printf("Problems with data!");
                else
                    printf("File was sorted!");
                fclose(f);
            }
            else
            {
                rc = ERR_FILE;
                printf("File is not created!");
            }
        }
    }
    else
    {
        rc = ERR_WRONG_CMD;
        printf("app.exe parametr file_name.txt\n"
            "Use these parametrs:\n\"c\" to create new file with random numbers;\n"
            "\"p\" to print numbers in file;\n\"s\" to sort numbers in file");
    }

    return rc;
}
