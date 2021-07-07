#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "base_manager.h"
#include "objects/camera.h"

namespace transformations{

using objects::Camera;

class CameraManager: public BaseManager {
public:
    void vertical(std::shared_ptr<Camera> camera, double angle);
    void longitudional(std::shared_ptr<Camera> camera, double angle);
    void transverse(std::shared_ptr<Camera> camera, double angle);
};

}

#endif
