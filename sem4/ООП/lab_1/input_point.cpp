#include "input_point.h"


// Обертка для fscanf
int read_counts(FILE *file, int &count_of_points, int &count_of_edges)
{
    if (fscanf(file, "%d %d", &count_of_points, &count_of_edges) != 2)
    {
        return ERR_READ;
    }
    return OK;
}

// Обертка для fscanf
int read_points(point_t *points, FILE *file, int i)
{
    if (fscanf(file, "%lf %lf %lf", &points[i].x, &points[i].y, &points[i].z) != 3)
    {
        return ERR_READ;
    }
    return OK;
}

// Обертка для fscanf
int read_edges(edge_t *edges, FILE *file, int i)
{
    if (fscanf(file, "%d->%d", &edges[i].first, &edges[i].second) != 2)
    {
        return ERR_READ;
    }
    return OK;
}

// Функция чтения количеств из файла
int read_counts_from_file(int *count_of_points, int *count_of_edges, stream_t &stream)
{
    if (get_file_from_stream_t(stream))
    {
        if (read_counts(get_file_from_stream_t(stream), *count_of_points, *count_of_edges) != OK)
        {
            return ERR_READ;
        }
    }
    else
    {
        return ERR_READ;
    }
    return OK;
}

// Функция чтения точек из файла
int read_points_from_file(point_t *points, int count_of_points, stream_t &stream)
{
    if (!get_file_from_stream_t(stream)) return ERR_READ;

    int code_error = OK;
        for (int i = 0; i < count_of_points && code_error == OK; i++)
        {
            if (read_points(points, get_file_from_stream_t(stream), i) != OK)
            {
                code_error = ERR_READ;
            }
        }

    return code_error;
}

// Функция чтения ребер из файла
int read_edges_from_file(edge_t *edges, int count_of_edges, stream_t &stream)
{
    int code_error = OK;
    if (get_file_from_stream_t(stream))
    {
        for (int i = 0; i < count_of_edges && code_error == OK; i++)
        {
            if (read_edges(edges, get_file_from_stream_t(stream), i) != OK)
            {
                code_error = ERR_READ;
            }
        }
    }
    else
    {
        code_error = ERR_READ;
    }
    return code_error;
}
