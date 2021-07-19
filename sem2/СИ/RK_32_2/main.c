#include "config.h"

int main(int args, char **argv)
{
    setbuf(stdout, NULL);
    if (!(args == 3 || args == 4))
    {
        printf("Wrong CMD! app.exe filename.txt action (list/select/sort)");
        return ERR_CMD;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Problems with file!");
        return ERR_FILE;
    }

    struct list_t *head = form_list(file);
    if (!head)
    {
        fclose(file);
        printf("MEMORY!");
        return ERR_MEMORY;
    }

    if (strcmp(argv[2], "list") == 0 && args == 3)  // Вывод их на экран
        print_list(head);
    else if (strcmp(argv[2], "select") == 0 && args == 4) // Выбор по подстроке
    {
        find_student(head, argv[3]);
    }
    else if (strcmp(argv[2], "sort") == 0 && args == 3) // Сортировка списка студентов
    {
        sort_student(&head);
        print_list(head);
    }
    else
    {
        fclose(file);
        free_list_t(head);
        printf("Wrong CMD! app.exe filename.txt action (list/select/sort) (surname of student for 'select')");
        return ERR_CMD;
    }

    free_list_t(head);
    fclose(file);

    return OK;
}
