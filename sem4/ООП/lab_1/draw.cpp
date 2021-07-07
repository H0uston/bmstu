#include "draw.h"

center_t center_init(void)
{
    center_t center;
    center.x = X / 2;
    center.y = Y / 2;
    return center;
}

void draw_axis(QGraphicsScene &scene)
{
    scene.addLine(X / 2, Y - Y, X / 2, Y);
    scene.addLine(X - X, Y / 2, X, Y / 2);
}

static void draw_ellipse(double sx, double sy, QGraphicsScene &scene)
{
    scene.addEllipse(sx, sy, 1, 1);
}

static void draw_points(point_t *p_res, shape_t shape, QGraphicsScene &scene)
{
    center_t center = center_init();
    int count_of_points = get_count_of_points(shape);
    for (int i = 0; i < count_of_points; i++)
    {
        double sx = center.x + get_x_index_point(shape, i);
        double sy = center.y + get_y_index_point(shape, i);
        p_res[i].x = sx;
        p_res[i].y = sy;
        draw_ellipse(sx, sy, scene);
    }
}

static void draw_line(point_2d_t &point_1, point_2d_t &point_2, QGraphicsScene &scene)
{
    scene.addLine(point_1.x, point_1.y, point_2.x, point_2.y);
}

static void draw_edges(point_t *p_res, shape_t shape, QGraphicsScene &scene)
{
    int count_of_edges = get_count_of_edges(shape);
    for (int i = 0; i < count_of_edges; i++)
    {
        point_2d_t point_1, point_2;
        point_1.x = static_cast<int>(get_x_coord_point(p_res[get_first_index_edge(shape, i)]));
        point_1.y = static_cast<int>(get_y_coord_point(p_res[get_first_index_edge(shape, i)]));
        point_2.x = static_cast<int>(get_x_coord_point(p_res[get_second_index_edge(shape, i)]));
        point_2.y = static_cast<int>(get_y_coord_point(p_res[get_second_index_edge(shape, i)]));
        draw_line(point_1, point_2, scene);
    }
}

int draw(shape_t shape, QGraphicsScene &scene)
{
    int code_error = OK;
    point_t p_res[get_count_of_points(shape)];

    draw_points(p_res, shape, scene);
    draw_edges(p_res, shape, scene);

    return code_error;
}
