#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    widget_width = 740;
    widget_height = 620;

    mode = DRAW_SEGMENT;

    bg_colour = Qt::white;
    segment_colour = Qt::black;
    cutter_colour = Qt::blue;
    cut_colour = Qt::red;

    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(bg_colour);

    setGeometry(20, 20, widget_width, widget_height);

    first_point_entered = false;
    {
        cutter_is_created = true;
        QPoint first_point = {200, 500};
        QPoint second_point = {500, 200};
        cutter = {{first_point}, {second_point}};
        QPainter painter(image);
        painter.setPen(cutter_colour);
        addCutter(painter, cutter);
    }
}

void PaintWidget::redrawImage()
{
    image->fill(bg_colour);
    QPainter painter(image);
    painter.setPen(segment_colour);
    for (size_t i = 0; i < segments.size(); i++)
    {
        addLine(painter, segments[i]);
    }

    if (cutter_is_created)
    {
        painter.setPen(cutter_colour);
        addCutter(painter, cutter);
    }

    // TODO Add cutted lines
    update();
}

void PaintWidget::drawBresenham(QPainter &painter, const QPoint &first, const QPoint &second)
{

    int xn = first.x();
    int yn = first.y();
    int xk = second.x();
    int yk = second.y();
    if (xn == xk && yn == yk)
    {
        painter.drawPoint(xk, yk);
    }
    else
    {
        int dx = xk - xn;
        int dy = yk - yn;
        int sx = sign(dx);
        int sy = sign(dy);
        dx = abs(dx);
        dy = abs(dy);
        bool exchange;
        if (dy > dx)
        {
            qSwap(dx, dy);
            exchange = true;
        }
        else
            exchange = false;
        int e = 2 * dy - dx;
        int x = xn, y = yn;
        for (int i = 0; i < dx + 1; i++)
        {
            painter.drawPoint(x, y);
            if (e >= 0)
            {
                if (exchange)
                    x += sx;
                else
                    y += sy;
                e -= 2 * dx;
            }
            if (exchange)
                y += sy;
            else
                x += sx;
            e += 2 * dy;
        }
    }
}

int PaintWidget::sign(int x)
{
    if (x > 0)
        return 1;
    else if (x == 0)
        return 0;
    return -1;
}

void PaintWidget::setBGColour(QColor &colour)
{
    bg_colour.setRgb(colour.rgb());
    redrawImage();
}

void PaintWidget::setSegmentColour(QColor &colour)
{
    segment_colour.setRgb(colour.rgb());
    redrawImage();
}

void PaintWidget::setCutterColour(QColor &colour)
{
    cutter_colour.setRgb(colour.rgb());
    redrawImage();
}

void PaintWidget::setCutColour(QColor &colour)
{
    cut_colour.setRgb(colour.rgb());
    redrawImage();
}

void PaintWidget::clear()
{
    image->fill(bg_colour);
    first_point_entered = false;
    segments.clear();
    // TODO cutted_lines.clear();
    redrawImage();
    update();
}

void PaintWidget::clearCutter()
{
    image->fill(bg_colour);
    cutter_is_created = false;
    redrawImage();
}

void PaintWidget::cutSegments()
{
    if (cutter_is_created)
    {
        rect = {cutter.first.x(), cutter.second.x(), cutter.first.y(), cutter.second.y()};
        for (size_t i = 0; i < segments.size(); i++)
        {
            coher_sutherland(segments[i]);
        }
    }
}

QVector<int> PaintWidget::get_code(QPoint& point)
{
    QVector<int> code = {0, 0, 0, 0};
    if (point.x() < rect[0])
        code[0] = 1;
    if (point.x() > rect[1])
        code[1] = 1;
    if (point.y() < rect[2])
        code[2] = 1;
    if (point.y() > rect[3])
        code[3] = 1;

    return code;
}

int PaintWidget::log_prod(QVector<int>& code1, QVector<int>& code2)
{
    int p = 0;
    for (size_t i = 0; i < 4; i++)
        p += code1[i] & code2[i];
    return p;
}

int PaintWidget::is_visiable(std::pair<QPoint, QPoint>& line)
{
    int s1 = 0;
    QVector<int> code1 = get_code(line.first);
    for (size_t i = 0; i < code1.size(); i++)
        s1 += code1[i];

    int s2 = 0;
    QVector<int> code2 = get_code(line.second);
    for (size_t i = 0; i < code2.size(); i++)
        s2 += code2[i];

    int vis = 2;

    if (!s1 && !s2)
        vis = 1;
    else
    {
        int l = log_prod(code1, code2);
        if (l != 0)
            vis = 0;
    }

    return vis;
}

void PaintWidget::coher_sutherland(std::pair<QPoint, QPoint>& line)
{
    QPainter painter(image);
    painter.setPen(cut_colour);
    bool flag = true; // инициализация флага общего полоэения
    double t = 1;
    int vis = 0;
    if (line.second.x() - line.first.x() == 0)
    {
        flag = -1;
    }
    else
    {
        t = (line.second.y() - line.first.y()) / (line.second.x() - line.first.x());
        if (t == 0)
            flag = 0;
    }

    for (size_t i = 0; i < 4; i++)
    {
        vis = is_visiable(line);
        if (vis == 1)
        {
            addLine(painter, line);
            return;
        }
        else if (vis == 0)
        {
            return;
        }

        QVector<int> code1 = get_code(line.first);
        QVector<int> code2 = get_code(line.second);

        if (code1[i] == code2[i])
            continue;

        if (!code1[i])
        {
            qSwap(line.first, line.second);
        }

        if (flag != -1)
        {
            if (i < 2)
            {
                line.first.ry() = t * (rect[i] - line.first.x()) + line.first.y();
                line.first.rx() = rect[i]; // TODO
            }
            else
            {
                line.first.rx() = (1 / t) * (rect[i] - line.first.y()) + line.first.x();
            }
        }
        line.first.ry() = rect[i];
    }
    addLine(painter, line);
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    if (mode == DRAW_SEGMENT)
    {
        QPainter painter(image);
        painter.setPen(QPen(segment_colour));
        if (event->button() == Qt::LeftButton)
        {
            if (event->modifiers() == Qt::ShiftModifier && (fabs(first_x - x) < fabs(first_y - y)))
            {
                x = first_x;
            }
            else if (event->modifiers() == Qt::ShiftModifier)
            {
                y = first_y;
            }

            if (first_point_entered)
            {
                segments.push_back({{first_x, first_y}, {x, y}});
                first_point_entered = false;
                addLine(painter, segments.back());
            }
            else
            {
                first_x = x;
                first_y = y;
                first_point_entered = true;
            }
        }
    }
    else if (mode == DRAW_CUTTER)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (first_point_entered)
            {
                QPainter painter(image);
                painter.setPen(QPen(cutter_colour));
                cutter = {{first_x, first_y}, {x, y}};
                first_point_entered = false;
                addCutter(painter, cutter);
            }
            else if (cutter_is_created)
            {
                QMessageBox msgBox;
                msgBox.setText("Уточнение");
                // Тип иконки сообщения
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setInformativeText("Отсекатель уже введен, ввести новый?");
                // На какой кнопке фокусироваться по умолчанию
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                int ret = msgBox.exec();
                switch (ret)
                {
                case QMessageBox::Yes:
                    cutter_is_created = false;
                    redrawImage();

                    first_x = x;
                    first_y = y;
                    first_point_entered = true;
                    break;
                default:
                    break;
                }
            }
            else
            {
                first_x = x;
                first_y = y;
                first_point_entered = true;
            }
        }
    }
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event);
}

void PaintWidget::addLine(QPainter &painter, std::pair<QPoint, QPoint> segment)
{
    const QPoint first_point = segment.first;
    const QPoint second_point = segment.second;
    drawBresenham(painter, first_point, second_point);
    update();
}

void PaintWidget::addCutter(QPainter &painter, std::pair<QPoint, QPoint> cutter)
{
    QPoint right_top = cutter.second;
    QPoint left_bottom = cutter.first;
    painter.drawRect(left_bottom.x(), left_bottom.y(),
                     fabs(left_bottom.x() - right_top.x()),
                     -fabs(left_bottom.y() - right_top.y()));
    cutter_is_created = true;
    update();
}

void PaintWidget::setDrawSegmentMode()
{
    mode = DRAW_SEGMENT;
    first_x = -1;
    first_y = -1;
    first_point_entered = false;
}

void PaintWidget::setDrawCutterMode()
{
    mode = DRAW_CUTTER;
    first_x = -1;
    first_y = -1;
    first_point_entered = false;
}
