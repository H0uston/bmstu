//
// Created by Houston on 15/12/2018.
//
#include "process.h"

/**
 * Ищет с конца строки подстроку
 * @param string строка, в которой производится поиск
 * @param substring подстрока, которую ищем
 * @return true, если нашлась, иначе false
 */
bool my_strstr(char *string, char *substring)
{
    if (string == NULL || substring == NULL)
        return false;
    int len_string = strlen(string);
    int len_substring = strlen(substring);
    int flag = 1;

    if (len_substring > len_string)
        return false;
    else
    {
        for (int i = 0; i < len_substring; i++)
        {
            if (string[len_string - i - 1] != substring[len_substring - i - 1])
            {
                flag = 0;
                break;
            }
        }

        if (flag == 1)
            return true;
        else
            return false;
    }
}

/**
 * Ищет студента по передаваемой подстроке. Если находит, то выводит его на экран
 * @param head указатель на начало списка
 * @param name подстрока
 */
void find_student(struct list_t *head, char *name)
{
    struct list_t *tmp = head;
    int flag = 1;

    while (tmp)
    {
        if (my_strstr(tmp->surname, name))
        {
            print_student(tmp);
            flag = 0;
        }
        tmp = tmp->next;
    }

    if (flag)
        printf("Empty!\n");
}

/**
 * Сортировка списка студентов выбором
 * @param head[in/out] указатель на начало списка
 */
void sort_student(struct list_t **head)
{
    assert(*head);
    struct list_t *prev = NULL; // Предыдущая запись
    struct list_t *next = NULL; // Следующая запись
    struct list_t *min = NULL; // Запись с "минимальной" строкой
    struct list_t *prev_min = NULL; // Запись перед "минимальной" строкой
    struct list_t *sorted = NULL; // Отсортированный список
    struct list_t *start_sorted = NULL; // Указатель на начало списка sorted
    while (*head)
    {
        prev = *head;
        next = (*head)->next;
        min = prev;
        while (next)
        {
            if (strcmp(min->surname, next->surname) > 0)
            {
                min = next;
                prev_min = prev;
            }
            else if (strcmp(min->surname, next->surname) == 0)
            {
                if (strcmp(min->name, next->name) > 0)
                {
                    min = next;
                    prev_min = prev;
                }
            }
            prev = next;
            next = next->next;
        }
        // Удаляю запись c "минимальной" строкой из исходного списка
        if (min == *head) // Если "минимальная" строка в исходнодном списке, расположена в начале, то сдвигаю исходный список
            *head = (*head)->next;
        else // Иначе элемент перед минимальным начинает указывать на "за минимальный"
            prev_min->next = min->next;

        // Формируется отсортированный список. Каждый раз добавляется новый "минимальный" элемент
        if (sorted == NULL)
            start_sorted = sorted = min;
        else
        {
            sorted->next = min;
            sorted = sorted->next;
        }
    }
    // Указываем на начало отсортированного списка
    *head = start_sorted;
}