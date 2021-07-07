#ifndef ADD_MODEL_COMMAND_H
#define ADD_MODEL_COMMAND_H

#include <string>
#include "../base_command.h"
#include "../../mediator/mediator.h"

namespace commands {

using mediator::Mediator;

class AddShapeCommand: public BaseCommand {
public:
    explicit AddShapeCommand(std::string file_name, std::string shape_name);
    void execute(std::shared_ptr<Mediator> mediator) override;
private:
    std::string _file_name;
    std::string _shape_name;
};

}

#endif
