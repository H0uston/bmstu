#ifndef FILE_OPEN_EXCEPTION_H
#define FILE_OPEN_EXCEPTION_H

#include "base_viewer_exception.h"

namespace exceptions {

class FileOpenException: public BaseViewerException {
public:
    FileOpenException() = default;
    explicit FileOpenException(std::string message): BaseViewerException(message) {}

    const char *what() const noexcept override {
        return "File wasn't opened";
    }
};

}

#endif
