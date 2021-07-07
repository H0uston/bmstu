#include "remove_shape_command.h"

namespace commands {

RemoveShapeCommand::RemoveShapeCommand(std::string object_name):
    _object_name(object_name) {}

void RemoveShapeCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    mediator->removeShape(_object_name);
}

}
