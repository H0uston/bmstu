#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <memory>
#include "../exceptions/object_type_exception.h"
#include "../math/point.h"
#include "../manager/draw_manager.h"
#include "../manager/transform_manager.h"
#include "../manager/camera_manager.h"
#include "../uploading/file_loader.h"
#include "../manager/shape_loader.h"
#include "../manager/scene_manager.h"
#include "../objects/shape.h"

namespace mediator {

using objects::Object;
using objects::Shape;
using objects::Camera;
using drawing::BaseDrawer;
using math::Point;

class Mediator {
public:
    Mediator();

    void addShape(std::string file_name, std::string shape_name);
    void addCamera(std::string cam_name);
    void setCamera(std::string cam_name);
    void removeCamera(std::string cam_name);
    void removeShape(std::string shape_name);

    void transformCamera(std::string cam_name, Point &move, Point &rotate);
    void transformShape(std::string shape_name, Point &move, Point &scale, Point &rotate);

    void draw(std::shared_ptr<BaseDrawer> drawer);
private:
    std::shared_ptr<drawing::DrawManager> _draw_manager;
    uploading::ShapeLoader _loader;
    transformations::TransformManager _transform_manager;
    transformations::CameraManager _cam_manager;
    scene::SceneManager _scene_manager;
};

}

#endif
