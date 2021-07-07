#include "my_paintwidget.h"

QPoint my_paintwidget::transform(point_3d &point, transform_params &p)
{
    rotate_point(point, p);
    int x = round(point.x * p.k);
    int y = round(point.y * p.k);
    return QPoint(x, y);
}

int sign(int x)
{
    if (x > 0)
        return 1;
    else if (x == 0)
        return 0;
    return -1;
}

void swap_num(int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void center_point(QPoint &p)
{
    p.setX(p.x() + X_CENTER);
    p.setY(p.y() + Y_CENTER);
}


void my_paintwidget::update_horizon(QPoint start, QPoint end)
{
    QPainter painter(&my_image);
    painter.setPen(QPen(color_draw));

    if (start.x() > end.x())
        qSwap(start, end);

    int dx = end.x() - start.x();
    int dy = end.y() - start.y();

    if (dx == 0)
    {
        top[start.x()] = qMax(start.y(), top[start.x()]);
        bottom[start.x()] = qMin(start.y(), bottom[start.x()]);
        center_point(start);
        center_point(end);
        painter.drawLine(start, end);
    }
    else
    {
        QPoint prev(start.x(), start.y());
        center_point(prev);
        double m = (dy) / (double)(dx);
        for (int x = start.x(); x <= end.x(); x++)
        {
            int y = round(m * (x - start.x()) + start.y());
            top[x] = qMax(top[x], y);
            bottom[x] = qMin(bottom[x], y);
            QPoint cur(x, y);
            center_point(cur);
            painter.drawLine(prev, cur);
            prev = cur;
        }
    }
}

QPoint my_paintwidget::calculate_cross(QPoint &prev, QPoint &cur, QHash<int, int> &array)
{
    int res_x = prev.x(), res_y = prev.y();
    int arr_y1 = array.value(prev.x()), arr_y2 = array.value(cur.x());
    int dx = cur.x() - prev.x();
    int dy_cur = cur.y() - prev.y();
    int dy_prev = arr_y2 - arr_y1;
    if (dx == 0)
    {
        res_x = cur.x();
        res_y = array.value(res_x);
    }
    else if (prev.y() == arr_y1 && cur.y() == arr_y2)
    {
        res_x = prev.x();
        res_y = prev.y();
    }
    else
    {
        double m = dy_cur / (double)(dx);
        if (dy_cur != dy_prev)
        {
            res_x = prev.x() - round(((prev.y() - arr_y1) * dx / (double)(dy_cur - dy_prev)));
            res_y = round((res_x - prev.x()) * m + prev.y());
        }
    }
    return QPoint(res_x, res_y);
}

int my_paintwidget::is_visible(QPoint &p)
{
    int x = p.x();
    int y = p.y();
    if (y < top[x] && y > bottom[x])
        return 0;
    if (y >= top[x])
        return 1;
    return -1;
}

my_paintwidget::my_paintwidget(QWidget *parent) : QWidget(parent)
{
    my_image = QImage(X_MAX, Y_MAX, QImage::Format_RGB32);
    my_image.fill(color_bg);
}

void my_paintwidget::set_draw_color(QColor &color)
{
    color_draw = color;
}

void my_paintwidget::clear()
{
    top.clear();
    bottom.clear();
    my_image.fill(color_bg);
}

void my_paintwidget::draw_surface(surface_data &surf, transform_params &p)
{
    this->clear();
    for (double i = -X_CENTER; i <= X_CENTER; i ++)
    {
        top.insert(i, -Y_CENTER);
        bottom.insert(i, Y_CENTER);
    }

    QPoint intersection;
    QPoint previous;
    QPoint current;
    QPoint left(-1, -1);
    QPoint right(-1, -1);

    bool flag_first_l = true;
    bool flag_first_r = true;
    int prev_visible;
    int cur_visible;

    double ax = p.angle_x;

    for (double z = surf.z_end; z >= surf.z_start; z -= surf.z_step)
    {
        double nz = z;
        if ((p.angle_x > 90 || p.angle_x < -90) && (p.angle_y > 90 || p.angle_y < -90))
            nz = z;
        else if (p.angle_x > 90 || p.angle_x < -90)
            nz = (surf.z_end - z) + surf.z_start;
        else if (p.angle_y > 90 || p.angle_y < -90)
            nz = (surf.z_end - z) + surf.z_start;

        double x_prev = surf.x_start;
        double y_prev = surf.func(x_prev, nz);
        point_3d prev = {x_prev, y_prev, nz};
        previous = transform(prev, p);

        if (!flag_first_l)
            update_horizon(left, previous);
        flag_first_l = false;
        left.setX(previous.x());
        left.setY(previous.y());

        prev_visible = is_visible(previous);

        double x, y;
        for (x = surf.x_start; x <= surf.x_end; x += surf.x_step)
        {
            y = surf.func(x, nz);
            point_3d cur = {x, y, nz};
            current = transform(cur, p);

            cur_visible = is_visible(current);

            if (prev_visible == cur_visible && (prev_visible == -1 || prev_visible == 1))
                update_horizon(previous, current);
            else
            {
                if (cur_visible == 0)
                {
                    if (prev_visible != 0)
                    {
                        intersection = (prev_visible == 1) ? calculate_cross(previous, current, top) : calculate_cross(previous, current, bottom);
                        update_horizon(previous, intersection);
                    }
                }
                else if (cur_visible == 1)
                {
                    if (prev_visible == 0)
                    {
                        intersection = calculate_cross(previous, current, top);
                        update_horizon(intersection, current);
                    }
                    else
                    {
                        intersection = calculate_cross(previous, current, bottom);
                        update_horizon(previous, intersection);
                        intersection = calculate_cross(previous, current, top);
                        update_horizon(intersection, current);
                    }
                }
                else
                {
                    if (prev_visible == 0)
                    {
                        intersection = calculate_cross(previous, current, bottom);
                        update_horizon(intersection, current);
                    }
                    else
                    {
                        intersection = calculate_cross(previous, current, top);
                        update_horizon(previous, intersection);
                        intersection = calculate_cross(previous, current, bottom);
                        update_horizon(intersection, current);
                    }
                }
            }
            prev_visible = cur_visible;
            previous.setX(current.x());
            previous.setY(current.y());
        }

        if (!flag_first_r)
            update_horizon(right, current);
        flag_first_r = false;
        right.setX(current.x());
        right.setY(current.y());
    }
}

void my_paintwidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, my_image);
}
