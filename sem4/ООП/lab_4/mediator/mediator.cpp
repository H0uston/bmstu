#include "mediator.h"

namespace mediator {

Mediator::Mediator():
    _draw_manager(new drawing::DrawManager),
    _loader(new uploading::FileLoader) {}

void Mediator::addShape(std::string file_name, std::string name) {
    std::shared_ptr<Shape> shape = _loader.loadShape(file_name, name);
    _scene_manager.getScene()->addShape(std::shared_ptr<objects::Shape>(shape));
}

void Mediator::addCamera(std::string name) {
    auto camera = new objects::Camera(name);
    _scene_manager.getScene()->addCamera(std::shared_ptr<objects::Camera>(camera));
}

void Mediator::setCamera(std::string cam_name) {
    _scene_manager.setCurrentCamera(cam_name);
}

void Mediator::removeCamera(std::string cam_name) {
    _scene_manager.getScene()->removeCamera(cam_name);
}

void Mediator::removeShape(std::string shape_name) {
    auto scene = _scene_manager.getScene();
    scene->removeShape(scene->getObject(shape_name));
}

void Mediator::transformCamera(std::string cam_name, math::Point &move, math::Point &rotate) {
    auto camera = _scene_manager.getScene()->getCamera(cam_name);
    _transform_manager.moveObject(camera, move.x(), move.y(), move.z());
    _cam_manager.longitudional(camera, rotate.x());
    _cam_manager.transverse(camera, rotate.y());
    _cam_manager.vertical(camera, rotate.z());
}

void Mediator::transformShape(std::string shape_name, math::Point &move, math::Point &scale, math::Point &rotate) {
    auto obj = _scene_manager.getScene()->getObject(shape_name);
    _transform_manager.moveObject(obj, move.x(), move.y(), move.z());
    _transform_manager.scaleObject(obj, scale.x(), scale.y(), scale.z());
    _transform_manager.rotateObjectX(obj, rotate.x());
    _transform_manager.rotateObjectY(obj, rotate.y());
    _transform_manager.rotateObjectZ(obj, rotate.z());
}

void Mediator::draw(std::shared_ptr<BaseDrawer> drawer) {
    _draw_manager->setDrawer(drawer);
    _draw_manager->setCamera(_scene_manager.getCurrentCamera());
    _scene_manager.getScene()->getShapesComposition()->accept(_draw_manager);
}

}
