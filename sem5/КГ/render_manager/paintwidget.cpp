#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    image = new QImage(_widget_width, _widget_height, QImage::Format_RGB32);
    image->fill(background_color);
    setGeometry(20, 20, _widget_width, _widget_height);
    _clipper = new Clipper();
}

std::vector<Triangle> PaintWidget::_triangulation(Triangle& triangle)
{
    std::vector<Triangle> triangles;
    std::vector<Point3D> points = triangle.get_points();
    for (size_t i = 0; i < points.size() - 2; i++)
    {
        Triangle tr(points[0], points[i + 1], points[i + 2]);
        Point3D vector = triangle.get_normal_vector();
        tr.set_normal_vector(vector);
        triangles.push_back(tr);
    }
    return triangles;
}

void PaintWidget::start_of_drawing()
{
    zbuffer.clear();
    image->fill(background_color);
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event)
}

static void viewport(Point3D& point)
{
    point.set_x((point.get_x() + 1) * 0.5 * WIDGET_WIDTH);
    point.set_y(WIDGET_HEIGHT - ((point.get_y() + 1) * 0.5 * WIDGET_HEIGHT));
    point.set_z((point.get_z() + 2) * 0.5);
}

Point3D PaintWidget::findBarycentricCoord(Point3D& p1, Point3D& p2, Point3D& p3, double x, double y, double square)
{
    Point3D b;
    b.set_x(((y - p3.get_y()) * (p2.get_x() - p3.get_x()) + (p2.get_y() - p3.get_y()) * (p3.get_x() - x)) / square);
    b.set_y(((y - p1.get_y()) * (p3.get_x() - p1.get_x()) + (p3.get_y() - p1.get_y()) * (p1.get_x() - x)) / square);
    b.set_z(1 - b.get_x() - b.get_y());
    return b;
}

void PaintWidget::fill_triangle(Triangle& triangle, QColor color)
{
    color = ambientLightning(triangle, color);
    for (auto &point: triangle.get_points())
    {
        viewport(point);
        point.set_z(1 / point.get_z());
    }

    QPoint leftCorner(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    QPoint rightCorner(0, 0);
    for (const auto &point: triangle.get_points())
    {
        rightCorner.setX(std::max(rightCorner.x(), static_cast<int>(point.get_x())));
        rightCorner.setY(std::max(rightCorner.y(),static_cast<int>(point.get_y())));
        leftCorner.setX(std::min(leftCorner.x(), static_cast<int>(point.get_x())));
        leftCorner.setY(std::min(leftCorner.y(), static_cast<int>(point.get_y())));
    }

    rightCorner.setX(std::min(rightCorner.x(), WIDGET_WIDTH - 1));
    rightCorner.setY(std::min(rightCorner.y(), WIDGET_HEIGHT - 1));

    Point3D& p0 = triangle.get_points()[0];
    Point3D& p1 = triangle.get_points()[1];
    Point3D& p2 = triangle.get_points()[2];
    double square = (p0.get_y() - p2.get_y()) * (p1.get_x() - p2.get_x()) +
            (p1.get_y() - p2.get_y()) * (p2.get_x() - p0.get_x());

    double start = leftCorner.x();
    double end = leftCorner.x() + (rightCorner.x() - leftCorner.x());

    Point3D barCoords;
    for (int i = round(start); i <= end; i++)
    {
        for (int j = leftCorner.y(); j <= rightCorner.y(); j++)
        {
            barCoords = findBarycentricCoord(p0, p1, p2, i, j, square);
            if (barCoords.get_x() >= -EPS && barCoords.get_y() >= -EPS && barCoords.get_z() >= -EPS)
            {
                double z = 1 / (barCoords.get_x() * p0.get_z() + barCoords.get_y() * p1.get_z() + barCoords.get_z() * p2.get_z());
                if (z <= zbuffer.At(i, j))
                {
                    zbuffer.set(i, j, z);
                    image->setPixel(i, j, color.rgb());
                }
            }
        }
    }
}

QColor PaintWidget::ambientLightning(Triangle& triangle, QColor objColor)
{
    Point3D normal = triangle.get_normal_vector();
    normal.normalize();
    return getColor(normal, objColor);
}

QColor PaintWidget::getColor(Point3D normal, QColor objColor)
{
    QColor lightColor(255, 255, 255);

    double intensity = lightVector ^ normal;
    intensity = std::max(intensity, 0.0);

    QColor tmp = objColor;
    double red = tmp.red();
    double green = tmp.green();
    double blue = tmp.blue();

    double reda = lightColor.redF();
    double greena = lightColor.greenF();
    double bluea = lightColor.blueF();

    reda *= 0.2;
    greena *= 0.2;
    bluea *= 0.2;

    reda += intensity;
    greena += intensity;
    bluea += intensity;

    red *= reda;
    green *= greena;
    blue *= bluea;

    if (green > 255)
        green = 255;
    else if (green != green)
        green = 0;
    if (red > 255)
        red = 255;
    else if (red != red)
        red = 0;
    if (blue > 255)
        blue = 255;
    else if (blue != blue)
        blue = 0;

    tmp.setRed(red);
    tmp.setBlue(blue);
    tmp.setGreen(green);

    return  tmp;

}

void PaintWidget::perspective_triangle(Triangle& triangles)
{
    std::vector<Point3D>& points = triangles.get_points();

    for (size_t i = 0; i < 3; i++)
    {
        points[i].set(points[i].get_x() / points[i].get_w(),
                      points[i].get_y() / points[i].get_w(),
                      points[i].get_z() / points[i].get_w());
    }
}

void PaintWidget::convert_to_world(Triangle& triangle, changes chn)
{
    std::vector<Point3D>& points = triangle.get_points();
    for (size_t i = 0; i < points.size(); i++)
    {
        Matrix new_coordinates(1, 4);
        new_coordinates[0][0] = points[i].get_x();
        new_coordinates[0][1] = points[i].get_y();
        new_coordinates[0][2] = points[i].get_z();
        new_coordinates[0][3] = points[i].get_w();
        new_coordinates = new_coordinates * chn.model_view * chn.camera_look * chn.projection;
        points[i].set(new_coordinates[0][0], new_coordinates[0][1], new_coordinates[0][2], new_coordinates[0][3]);
    }
}

void PaintWidget::_work_with_triangle(Triangle triangle, changes chn, QColor color)
{
    int count_of_points = 0;
    convert_to_world(triangle, chn);
    count_of_points = _clipper->clip_polygon(triangle);
    if (count_of_points > 3) // New points appeared TODO
    {
        std::vector<Triangle> new_triangles = _triangulation(triangle);
        for (size_t i = 0; i < new_triangles.size(); i++)
        {
            perspective_triangle(new_triangles[i]);
            fill_triangle(new_triangles[i], color);
        }
        return;
    }
    else if (count_of_points < 3) // triangle is invisible
    {
        return;
    }
    perspective_triangle(triangle);

    fill_triangle(triangle, color);
}

void PaintWidget::_render_polygon(const Polygon& polygon, const QColor color, const changes chn)
{
    std::vector<Triangle> triangles = polygon.get_triangles();
    size_t trg_count = polygon.get_count_of_triangles();
    for (size_t i = 0; i < trg_count; i ++)
    {
        if (polygon.get_name() == "wheel_l" && (i == 0 || i == 1 || i == 6 || i == 7))
            _work_with_triangle(triangles[i], chn, Qt::red);
        else if (polygon.get_name() == "wheel_r" && (i == trg_count - 2 || i == trg_count - 1 || i == trg_count - 7 || i == trg_count - 8))
            _work_with_triangle(triangles[i], chn, Qt::red);
        else
            _work_with_triangle(triangles[i], chn, color);
    }
}
