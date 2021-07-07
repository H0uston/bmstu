#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "../base_command.h"
#include "../../math/point.h"
#include "../../mediator/mediator.h"

namespace commands {

using mediator::Mediator;
using math::Point;

class TransformShapeCommand: public BaseCommand {
public:
    TransformShapeCommand(std::string object_name, Point move, Point scale, Point rotate);
    void execute(std::shared_ptr<Mediator> mediator) override;
private:
    std::string _object_name;
    Point _move;
    Point _scale;
    Point _rotate;
};

}

#endif
