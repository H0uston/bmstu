#include "vertical_axis_camera_command.h"

namespace commands {

VerticalCameraCommand::VerticalCameraCommand(std::string object_name, double angle):
    _object_name(object_name), _rotation(0, 0, angle) {}

void VerticalCameraCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    math::Point moving(0, 0, 0);
    mediator->transformCamera(_object_name, moving, _rotation);
}

}
