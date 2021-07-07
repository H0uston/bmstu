#ifndef SET_CAMERA_H
#define SET_CAMERA_H

#include <string>
#include "../base_command.h"
#include "../../mediator/mediator.h"

namespace commands {

class SetCameraCommand: public BaseCommand {
public:
    explicit SetCameraCommand(std::string name);
    void execute(std::shared_ptr<Mediator> mediator) override;
private:
    std::string _name;
};

}

#endif
