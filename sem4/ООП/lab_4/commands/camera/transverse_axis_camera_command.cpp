#include "transverse_axis_camera_command.h"

namespace commands {

TransverseCameraCommand::TransverseCameraCommand(std::string object_name, double angle):
    _object_name(object_name), _rotation(0, angle, 0) {}

void TransverseCameraCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    math::Point moving(0, 0, 0);
    mediator->transformCamera(_object_name, moving, _rotation);
}

}
