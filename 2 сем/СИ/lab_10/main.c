#include "config.h"

int main(int args, char **argv)
{
    setbuf(stdout, NULL);
    int status = OK;

    if ((args < MIN_ARGV || args > MAX_ARGV) && args != 3)
        status = ERR_CMD;

    if (status == OK)
    {
        switch (args)
        {
            case 2:
                if (!strcmp(argv[1], "h"))
                    organize_info();
                else
                    status = ERR_PARAM;
                break;
            case 4:
                if (!strcmp(argv[1], "d"))
                    status = organize_pop_back(argv[2], argv[3]);
                else if (!strcmp(argv[1], "s"))
                    status = organize_sort(argv[2], argv[3]);
                break;
            case 5:
                if (!strcmp(argv[1], "a"))
                    status = organize_append(argv[2], argv[3], argv[4]);
                else if (!strcmp(argv[1], "f"))
                    status = organize_find(argv[2], argv[3], argv[4]);
                break;
        }
    }

    switch (status)
    {
        case OK:
            printf("Program successfully finished.");
            break;
        case ERR_CMD:
            printf("Wrong CMD!");
            break;
        case ERR_PARAM:
            printf("Unknown action.");
            break;
        case ERR_FILE:
            printf("Wrong file!");
            break;
        default:
            printf("Unknown error");
            break;
    }

    return status;
}