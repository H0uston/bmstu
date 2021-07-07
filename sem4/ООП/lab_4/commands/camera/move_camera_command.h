#ifndef MOVE_CAMERA_COMMAND_H
#define MOVE_CAMERA_COMMAND_H

#include "../base_command.h"
#include "../../math/point.h"
#include "../../mediator/mediator.h"

namespace commands {

using mediator::Mediator;
using math::Point;

class MoveCameraCommand: public BaseCommand {
public:
    MoveCameraCommand(std::string object_name, Point move);
    void execute(std::shared_ptr<Mediator> mediator) override;
private:
    std::string _object_name;
    Point _move;
};

}

#endif
