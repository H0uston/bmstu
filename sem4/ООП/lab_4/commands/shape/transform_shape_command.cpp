#include "transform_shape_command.h"

namespace commands {

TransformShapeCommand::TransformShapeCommand(std::string object_name, math::Point move, math::Point scale, math::Point rotate):
    _object_name(object_name), _move(move), _scale(scale), _rotate(rotate) {}

void TransformShapeCommand::execute(std::shared_ptr<mediator::Mediator> mediator)
{
    mediator->transformShape(_object_name, _move, _scale, _rotate);
}

}
