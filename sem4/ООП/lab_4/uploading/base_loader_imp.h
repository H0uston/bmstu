#ifndef BASE_LOADER_H
#define BASE_LOADER_H

#include <string>
#include "../objects/shape.h"

namespace uploading {

using objects::Shape;

class BaseLoader {
public:
    virtual ~BaseLoader() = default;

    virtual void open(std::string source_name) = 0;
    virtual void close() = 0;
    virtual std::pair<size_t, size_t> readShapeInfo() = 0;
    virtual std::pair<size_t, size_t> readEdgeInfo() = 0;
    virtual math::Point readPoint() = 0;
};

}

#endif
