#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "../mediator/mediator.h"

namespace commands {

using mediator::Mediator;

class BaseCommand
{
public:
    virtual ~BaseCommand() = default;
    virtual void execute(std::shared_ptr<Mediator> mediator) = 0;
};

}

#endif
