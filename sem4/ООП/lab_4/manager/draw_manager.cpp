#include "draw_manager.h"

namespace drawing {

void DrawManager::setDrawer(std::shared_ptr<BaseDrawer> drawer) {
    _drawer = drawer;
}

void DrawManager::setCamera(std::shared_ptr<Camera> camera) {
    _camera = camera;
}

void DrawManager::visit(Shape &shape) {
    if (!_drawer || !_camera) {
        throw exceptions::DrawerInitException("Drawer or camera wasn't set");
    }
    auto mesh = shape.getMesh();
    auto lines = mesh->getLines();
    for (auto &line: lines) {
        proectPoint(line.first);
        proectPoint(line.second);
        _drawer->drawLine(line.first, line.second);
    }
}

void DrawManager::visit(Composition&) {}

void DrawManager::visit(Camera&) {}

void DrawManager::proectPoint(math::Point &p) {
    auto cam_pos = _camera->getPosition();
    std::shared_ptr<Matrix> transform_matrix(new MoveMatrix(-cam_pos.x(), -cam_pos.y(), 0));
    p.transform(transform_matrix);
    transform_matrix.reset(new RotateOxMatrix(-_camera->getXAngle()));
    p.transform(transform_matrix);
    transform_matrix.reset(new RotateOyMatrix(-_camera->getYAngle()));
    p.transform(transform_matrix);
    transform_matrix.reset(new RotateOzMatrix(-_camera->getZAngle()));
    p.transform(transform_matrix);

    double eps = 1e-10;
    double znam = p.z() + cam_pos.z();
    if (znam < eps && znam > -eps) {
        znam = eps;
    }
    double distCoef = cam_pos.z() / znam;
    p.setX(p.x() * distCoef);
    p.setY(p.y() * distCoef);
}

} // namespace render
