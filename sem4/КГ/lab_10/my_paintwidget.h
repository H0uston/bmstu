#ifndef MY_PAINTWIDGET_H
#define MY_PAINTWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPair>
#include <QHash>

#include "functions.h"
#include "math_module.h"

#define X_MAX 600
#define Y_MAX 600
#define X_CENTER 300
#define Y_CENTER 300

class my_paintwidget : public QWidget
{
    Q_OBJECT

private:
    QColor color_draw = QColor(Qt::white);
    QColor color_bg = QColor(Qt::black);
    QImage my_image;

    QHash <int, int> top;
    QHash <int, int> bottom;

    QPoint transform(point_3d &point, transform_params &p);
    void update_horizon(QPoint start, QPoint end);
    QPoint calculate_cross(QPoint &prev, QPoint &cur, QHash<int, int> &array);
    int is_visible(QPoint &p);

public:
    explicit my_paintwidget(QWidget *parent = nullptr);

    void set_draw_color(QColor &color);
    void clear(void);
    void draw_surface(surface_data &surf, transform_params &p);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MY_PAINTWIDGET_H
