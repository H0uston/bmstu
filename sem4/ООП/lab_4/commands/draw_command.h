#ifndef DRAW_COMMAND_H
#define DRAW_COMMAND_H

#include "base_command.h"
#include "../mediator/mediator.h"

namespace commands {

using mediator::Mediator;

class DrawCommand: public BaseCommand {
public:
    explicit DrawCommand(std::shared_ptr<drawing::BaseDrawer> drawer);
    void execute(std::shared_ptr<Mediator> mediator) override;
private:
    std::shared_ptr<drawing::BaseDrawer> _drawer;
};

}

#endif
