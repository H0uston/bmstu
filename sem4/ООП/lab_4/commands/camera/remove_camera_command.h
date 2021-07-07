#ifndef REMOVE_CAMERA_COMMAND_H
#define REMOVE_CAMERA_COMMAND_H

#include "../base_command.h"
#include "mediator/mediator.h"

namespace commands {

class RemoveCameraCommand: public BaseCommand {
public:
    RemoveCameraCommand(std::string object_name);
    void execute(std::shared_ptr<Mediator> mediator) override;
private:
    std::string _object_name;
};

}

#endif
