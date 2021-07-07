#include "scene.h"

namespace scene {

Scene::Scene(): _objects(new Composition) {}

void Scene::removeShape(std::shared_ptr<Object> obj)
{
    ssize_t i = _objects->getIndex(obj);
    if (i > -1)
    {
        _objects->remove(size_t(i));
    }
}

void Scene::removeCamera(std::string cam_name)
{
    _cameras.erase(cam_name);
}

std::shared_ptr<Composition> Scene::getShapesComposition()
{
    return _objects;
}

std::shared_ptr<Camera> Scene::getCamera(std::string cam_name)
{
    return _cameras.at(cam_name);
}

std::shared_ptr<Object> Scene::getObject(std::string shape_name)
{
    auto objects = _objects->getObjects();
    for (auto &obj: objects)
    {
        if (obj->getName() == shape_name)
        {
            return obj;
        }
    }

    throw exceptions::ObjectSearchException();
}

void Scene::addShape(std::shared_ptr<Shape> obj)
{
    _objects->add(obj);
}

void Scene::addCamera(std::shared_ptr<Camera> obj)
{
    _cameras.emplace(obj->getName(), obj);
}

std::vector<std::shared_ptr<Object>> Scene::getObjects()
{
    return _objects->getObjects();
}

}
