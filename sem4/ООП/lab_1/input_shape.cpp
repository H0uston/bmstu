#include "input_shape.h"

// Функция проверки на индексы, не больше ли они, чем кол-во точек в модели
static int check_input(shape_t &shape)
{
    if (shape.count_of_edges <= 0 || shape.count_of_points <= 0)
    {
        return ERR_READ;
    }

    for (int i = 0; i < shape.count_of_edges; i++)
    {
        if (shape.count_of_points <= shape.edges[i].first || shape.count_of_points <= shape.edges[i].second)
        {
            return ERR_READ;
        }
    }

    return OK;
}

// Функция чтения модели
static int read_shape(shape_t &shape, stream_t &stream)
{
    int code_error = read_counts_from_file(&shape.count_of_points, &shape.count_of_edges, stream);

    if (code_error != OK)
    {
        return code_error;
    }

    code_error = allocate_shape(shape);

    if (code_error != OK)
    {
        return code_error;
    }

    code_error = read_points_from_file(shape.points, shape.count_of_points, stream);

    if (code_error == OK)
    {
        code_error = read_edges_from_file(shape.edges, shape.count_of_edges, stream);
    }

    if (code_error == OK)
    {
        code_error = check_input(shape);
    }

    if (code_error != OK)
    {
        free_shape(shape);
    }

    return code_error;
}

// Функция чтения модели
int file_reader(shape_t &shape, parameters_t &parameters)
{
    stream_t stream = stream_init();
    int code_error = file_openning_read(stream, parameters.filename);

    if (code_error != OK)
    {
        return code_error;
    }

    shape_t tmp = init();
    code_error = read_shape(tmp, stream);
    close_stream(stream);
    if (code_error == OK)
    {
        free_shape(shape);
        shape = tmp;
    }

    return code_error;
}
