#ifndef ADD_CAMERA_COMMAND_H
#define ADD_CAMERA_COMMAND_H

#include <string>
#include "../base_command.h"
#include "../../mediator/mediator.h"

namespace commands {

class AddCameraCommand: public BaseCommand {
public:
    explicit AddCameraCommand(std::string name);
    void execute(std::shared_ptr<Mediator> mediator) override;
private:
    std::string _name;
};

}

#endif
