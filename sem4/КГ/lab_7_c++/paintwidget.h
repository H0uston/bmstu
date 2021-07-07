#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <cmath>
#include <QtCore>
#include <QMessageBox>
#include <algorithm>

enum Mode {DRAW_SEGMENT, DRAW_CUTTER};

class PaintWidget : public QWidget
{

    Q_OBJECT

public:
    explicit PaintWidget(QWidget* parent = nullptr);
    void setBGColour(QColor& colour);
    void setSegmentColour(QColor& colour);
    void setCutterColour(QColor& color);
    void setCutColour(QColor& color);
    void clear();
    void clearCutter();
    void cutSegments();
    void setDrawSegmentMode();
    void setDrawCutterMode();

    bool cutter_is_created;

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Mode mode;
    QColor bg_colour;
    QColor segment_colour;
    QColor cutter_colour;
    QColor cut_colour;

    QVector<std::pair<QPoint, QPoint>> segments;

    std::pair<QPoint, QPoint> cutter;

    QImage *image;
    int widget_height;
    int widget_width;

    int first_x;
    int first_y;

    bool drawing_enabled;
    bool first_point_entered;

    QVector<int> rect;

    void redrawImage();

    void addLine(QPainter &painter, std::pair<QPoint, QPoint> segment);
    void addCutter(QPainter &painter, std::pair<QPoint, QPoint> cutter);

    void drawBresenham(QPainter &painter, const QPoint &first, const QPoint &second);
    void coher_sutherland(std::pair<QPoint, QPoint>& line);
    int is_visiable(std::pair<QPoint, QPoint>& line);
    int log_prod(QVector<int>& code1, QVector<int>& code2);
    QVector<int> get_code(QPoint& point);

    int sign(int x);
};

#endif // DRAWWIDGET_H
