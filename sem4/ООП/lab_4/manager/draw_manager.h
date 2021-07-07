#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <memory>
#include "base_manager.h"
#include "../render/base_drawer.h"
#include "../exceptions/drawer_exception.h"
#include "../visitor/visitor.h"
#include "../objects/composition.h"
#include "../objects/shape.h"
#include "../objects/camera.h"
#include "../math/point.h"
#include "../math/transform_matrix.h"

namespace drawing {

using namespace math;
using namespace objects;

class DrawManager: public Visitor, public BaseManager {
public:
    void setDrawer(std::shared_ptr<BaseDrawer> drawer);
    void setCamera(std::shared_ptr<Camera> camera);
    void visit(Shape &shape) override;
    void visit(Composition &composite) override;
    void visit(Camera &camera) override;

private:
    std::shared_ptr<BaseDrawer> _drawer;
    std::shared_ptr<Camera> _camera;

    void proectPoint(Point &point);
};

}

#endif
