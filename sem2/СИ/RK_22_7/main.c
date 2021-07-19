#include "config.h"
#include "errors.h"

int main(int argc, char *argv[])
{
    int rc = OK, n;
    float a[N], border;
    FILE *f;

    if (argc != 2)
    {
        printf("Wrong paramets! app.exe file_name.txt");
        rc = ERR_WRONG_CMD;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (f == NULL)
        {
            printf("File does not exist!");
            rc = ERR_FILE;
        }
        else
        {
            rc = arr_input(f, a, &n);
            if (rc == OK)
            {
                arr_print(a, n);
                printf("Enter border: ");
                if (scanf("%f", &border) == 1)
                {
                    process(a, n, border);
                    arr_print(a, n);
                }
                else
                {
                    printf("Wrong value of border!");
                    rc = ERR_RANGE;
                }
            }
            else if (rc == ERR_CNT)
                printf("Wrong count of numbers in file!");
            else if (rc == ERR_RANGE)
                printf("Wrong value of count of numbers!");
        }
        fclose(f);
    }

    return rc;
}
