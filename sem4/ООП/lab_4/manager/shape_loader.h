#ifndef SHAPE_LOADER_H
#define SHAPE_LOADER_H

#include "../uploading/shape_builder.h"
#include "../uploading/abs_shape_loader.h"
#include "memory"
#include "../uploading/base_loader_imp.h"

namespace uploading {

using objects::Shape;

class ShapeLoader: public AbsShapeLoader {
public:
    explicit ShapeLoader(BaseLoader *loader);
    std::shared_ptr<Shape> loadShape(std::string source_name, std::string shape_name) override;
private:
    std::unique_ptr<BaseLoader> _loader;
    std::unique_ptr<ShapeBuilder> _builder;
};

}

#endif
