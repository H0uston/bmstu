Лабораторная работа №10. Выполнил Уласик Евгений ИУ7-31Б.

Функции для реализации:
1) node_t* find(node_t *head, const void *data, int (*comparator)(const void*, const void *));
2) void* pop_back(node_t **head);
3) void append(node_t **head_a, node_t **head_b);
4) void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

Задача: Написать программу, которая производит некоторую (в рамках реализованных функций) работу с данными
об объектах Солнечной системы.

Память под структуры выделяются динамически. Структура хранит указатели на название планеты (строку)
и ее диаметр (вещественное число).

Исходные данные читаются из файла, результирующие выводятся в файл.
Имена файлов и выполняемая операция указывается через параметры командной строки. Формат запуска:

app.exe action file_in_1.txt [file_in_2.txt] file_out.txt [string]

Для выдачи справочной информации по action предлагается запустить программу
со следующими параметрами:

app.exe h

Допущение:
1) Данные для структуры хранятся на каждой новой строчке файла.
2) Название планет не должно превышать 80 символов.
3) Диаметр планеты должен быть числом, не выходящим за численный диапазон типа double.