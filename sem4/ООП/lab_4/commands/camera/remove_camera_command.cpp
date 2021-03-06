#include "remove_camera_command.h"

namespace commands {

RemoveCameraCommand::RemoveCameraCommand(std::string object_name):
    _object_name(object_name) {}

void RemoveCameraCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    mediator->removeCamera(_object_name);
}

}
