#ifndef SHAPE_BUILD_EXCEPTION_H
#define SHAPE_BUILD_EXCEPTION_H

#include "base_viewer_exception.h"

namespace exceptions {

class ShapeBuildException: public BaseViewerException{
public:
    ShapeBuildException() = default;
    explicit ShapeBuildException(std::string message): BaseViewerException(message) {}

    const char *what() const noexcept override
    {
        return "Error while building model";
    }
};

}

#endif
