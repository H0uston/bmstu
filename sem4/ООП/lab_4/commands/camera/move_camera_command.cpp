#include "move_camera_command.h"

namespace commands {

MoveCameraCommand::MoveCameraCommand(std::string object_name, math::Point move):
    _object_name(object_name), _move(move) {}

void MoveCameraCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    math::Point rotation(0, 0, 0);
    mediator->transformCamera(_object_name, _move, rotation);
}

} // namespace commands
