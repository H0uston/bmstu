#ifndef SCENE_H
#define SCENE_H

#include <unordered_map>
#include <memory>
#include "../exceptions/camera_lack_exception.h"
#include "../exceptions/object_search_exception.h"
#include "../objects/composition.h"
#include "../objects/shape.h"
#include "../objects/camera.h"

namespace scene {

using namespace objects;

class Scene {
public:
    Scene();

    void addShape(std::shared_ptr<Shape> obj);
    void addCamera(std::shared_ptr<Camera> obj);
    void removeShape(std::shared_ptr<Object> obj);
    void removeCamera(std::string cam_name);

    std::shared_ptr<Composition> getShapesComposition();
    std::shared_ptr<Camera> getCamera(std::string cam_name);
    std::shared_ptr<Object> getObject(std::string shape_name);
    std::vector<std::shared_ptr<Object>> getObjects();
private:
    std::shared_ptr<Composition> _objects;
    std::unordered_map<std::string, std::shared_ptr<Camera>> _cameras;
};

} // namespace scene

#endif //LAB4_SCENE_H
