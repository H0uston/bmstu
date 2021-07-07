#include "commands/camera/longitudinal_axis_camera_command.h"

namespace commands {

LongitudinalCameraCommand::LongitudinalCameraCommand(std::string object_name, double angle):
    _object_name(object_name), _rotation(angle, 0, 0) {}

void LongitudinalCameraCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    math::Point moving(0, 0, 0);
    mediator->transformCamera(_object_name, moving, _rotation);
}

} // namespace commands
