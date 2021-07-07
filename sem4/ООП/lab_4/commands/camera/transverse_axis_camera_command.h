#ifndef PITCH_CAMERA_COMMAND_H
#define PITCH_CAMERA_COMMAND_H

#include "../base_command.h"
#include "math/point.h"
#include "mediator/mediator.h"

namespace commands {

class TransverseCameraCommand: public BaseCommand {
public:
    TransverseCameraCommand(std::string object_name, double angle);
    void execute(std::shared_ptr<Mediator> mediator) override;
private:
    std::string _object_name;
    math::Point _rotation;
};

}

#endif
