#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <thread>

#include "../model/model.h"
#include "config.h"
#include "zbuffer.h"
#include "clipper.h"

struct Params
{
    int startRow;
    int endRow;
    int startCol;
    int endCol;
};

struct Triangle_points
{
    Point3D p0;
    Point3D p1;
    Point3D p2;
};

struct changes
{
    Matrix model_view;
    Matrix camera_look;
    Matrix projection;
    Matrix rotate;
};

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void fill_triangle(Triangle& triangle, QColor color);
    void start_of_drawing();
    void _render_polygon(const Polygon& polygon, const QColor color, const changes chn);

private slots:
    void paintEvent(QPaintEvent *event);

private:
    Point3D findBarycentricCoord(Point3D& p1, Point3D& p2, Point3D& p3, double x, double y, double square);
    void _work_with_triangle(Triangle triangle, changes chn, QColor color);
    std::vector<Triangle> _triangulation(Triangle& triangle);
    void perspective_triangle(Triangle& triangles);
    void convert_to_world(Triangle& triangle, changes chn);
    void draw_triangle(Params param, Triangle triangle, QColor color, const double square);
    int _widget_width = WIDGET_WIDTH;
    int _widget_height = WIDGET_HEIGHT;
    int _widget_center_width = WIDGET_CENTER_WIDTH;
    int _widget_center_height = WIDGET_CENTER_HEIGHT;
    QColor ambientLightning(Triangle& triangle, QColor objColor);
    QColor getColor(Point3D normal, QColor objColor);

    ZBuffer zbuffer = ZBuffer(_widget_width + 20, _widget_height + 20);

    QImage *image;
    QColor background_color = SKY;
    Clipper* _clipper;

    Point3D lightVector = Point3D(0, 0, 1);
};

#endif // PAINTWIDGET_H
