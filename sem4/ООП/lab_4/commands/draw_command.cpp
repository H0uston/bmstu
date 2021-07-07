#include "draw_command.h"

namespace commands {

DrawCommand::DrawCommand(std::shared_ptr<drawing::BaseDrawer> drawer):
    _drawer(drawer) {}

void DrawCommand::execute(std::shared_ptr<Mediator> mediator)
{
    mediator->draw(_drawer);
}

}
