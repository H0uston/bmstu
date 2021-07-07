#include "output.h"

// Функция обертка для fscanf (запись)
static void print_counts(FILE *file, int count_of_points, int count_of_edges)
{
    fprintf(file, "%d %d\n", count_of_points, count_of_edges);
}

// Функция обертка для fscanf (запись)
static void print_points(shape_t &shape, FILE *file, int i)
{
    fprintf(file, "%lf %lf %lf\n", get_x_index_point(shape, i), get_y_index_point(shape, i), get_z_index_point(shape, i));
}

// Функция обертка для fscanf (запись)
static void print_edges(shape_t &shape, FILE *file, int i)
{
    fprintf(file, "%d->%d\n", get_first_index_edge(shape, i), get_second_index_edge(shape, i));
}

// Функция сохранения модели в файл
int save_shape(shape_t &shape, parameters_t &parameters)
{
    int code_error = OK;
    if (!shape.points || !shape.edges)
    {
        code_error = ERR_SAVE;
        return code_error;
    }
    stream_t stream = stream_init();
    code_error = file_openning_save(stream, parameters.filename);
    if (code_error == OK)
    {
        int n = get_count_of_points(shape);
        int m = get_count_of_edges(shape);
        print_counts(get_file_from_stream_t(stream), n, m);
        for (int i = 0; i < n; i++)
        {
            print_points(shape, get_file_from_stream_t(stream), i);
        }

        for (int i = 0; i < m; i++)
        {
            print_edges(shape, get_file_from_stream_t(stream), i);
        }
        close_stream(stream);
    }
    else
    {
        code_error = ERR_SAVE;
        return code_error;
    }
    return code_error;
}
