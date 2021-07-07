#include "add_shape_command.h"

namespace commands {

AddShapeCommand::AddShapeCommand(std::string file_name, std::string shape_name):
    _file_name(file_name), _shape_name(shape_name) {}

void AddShapeCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    mediator->addShape(_file_name, _shape_name);
}

}
