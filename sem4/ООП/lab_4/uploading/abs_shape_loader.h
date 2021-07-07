#ifndef ABS_SHAPE_LOADER_H
#define ABS_SHAPE_LOADER_H

#include "memory"
#include "base_loader_imp.h"
#include "objects/shape.h"

namespace uploading {

using objects::Shape;

class AbsShapeLoader {
public:
    AbsShapeLoader() = default;
    virtual ~AbsShapeLoader() = default;
    virtual std::shared_ptr<Shape> loadShape(std::string source_name, std::string shape_name) = 0;
};

}

#endif
