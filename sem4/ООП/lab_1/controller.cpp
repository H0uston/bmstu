#include "controller.h"

int controller(QGraphicsScene &scene, parameters_t parameters, int action) {
    static shape_t shape = init();

    int code_error = OK;

    switch (action)
    {
    case LOAD:
        code_error = file_reader(shape, parameters);
        break;
    case SAVE:
        code_error = save_shape(shape, parameters);
        break;
    case ROTATE_X:
        code_error = rotate_x(shape, parameters);
        break;
    case ROTATE_Y:
        code_error = rotate_y(shape, parameters);
        break;
    case ROTATE_Z:
        code_error = rotate_z(shape, parameters);
        break;
    case SCALE:
        code_error = scale(shape, parameters);
        break;
    case MOVE:
        code_error = move(shape, parameters);
        break;
    case DRAW:
        code_error = set_view(shape, scene);
        break;
    case FREE_MEMORY:
        code_error = free_memory(shape);
        break;
    default:
        code_error = UNKNOWN_PROBLEM;
        break;
    }
    return code_error;
}
