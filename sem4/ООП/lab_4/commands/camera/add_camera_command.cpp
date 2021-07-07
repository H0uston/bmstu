#include "commands/camera/add_camera_command.h"

namespace commands {

AddCameraCommand::AddCameraCommand(std::string name): _name(name) {}

void AddCameraCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    mediator->addCamera(_name);
}

} // namespace commands
