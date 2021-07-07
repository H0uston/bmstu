#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <memory>
#include "paintwidget.h"
#include "math/point.h"
#include "commands/shape/add_shape_command.h"
#include "commands/draw_command.h"
#include "commands/camera/set_camera.h"
#include "commands/camera/add_camera_command.h"
#include "commands/shape/transform_shape_command.h"
#include "commands/camera/vertical_axis_camera_command.h"
#include "commands/camera/longitudinal_axis_camera_command.h"
#include "commands/camera/transverse_axis_camera_command.h"
#include "commands/shape/transform_shape_command.h"
#include "commands/camera/move_camera_command.h"
#include "commands/shape/remove_shape_command.h"
#include "commands/camera/remove_camera_command.h"
#include "exceptions/file_open_exception.h"
#include "exceptions/camera_lack_exception.h"
#include "facade/facade.h"
#include "render/qt_drawer.h"

namespace Ui {
class Widget;
}

using facade::Facade;
using math::Point;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void moveObject();
    void scaleObject();
    void rotateObjectX();
    void rotateObjectY();
    void rotateObjectZ();

    void addShape();
    void addCamera();
    void removeObject();
    void setCamera();

private:
    Ui::Widget *ui;
    DrawLabel *_draw_label;
    QPixmap _pixmap;
    std::unique_ptr<Facade> _facade;
    size_t _elements_num;

    void render();
};

#endif // WIDGET_H
