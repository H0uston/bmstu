#ifndef FACADE_H
#define FACADE_H

#include "../mediator/mediator.h"
#include "../commands/base_command.h"

namespace facade {

using mediator::Mediator;
using commands::BaseCommand;

class Facade {
public:
    Facade();
    void execute_command(BaseCommand *command);
private:
    std::shared_ptr<Mediator> _mediator;
};

}

#endif
