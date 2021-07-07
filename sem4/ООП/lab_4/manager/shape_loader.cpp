#include "shape_loader.h"

namespace uploading {

ShapeLoader::ShapeLoader(BaseLoader *loader): _loader(loader), _builder(new ShapeBuilder()) {}

std::shared_ptr<objects::Shape> ShapeLoader::loadShape(std::string source_name, std::string shape_name)
{
    _loader->open(source_name);
    _builder->reset(shape_name);

    std::pair<size_t, size_t> shape_info = _loader->readShapeInfo();

    for (size_t i = 0; i < shape_info.first; i++)
    {
        math::Point p = _loader->readPoint();
        _builder->addPoint(p);
    }

    for (size_t i = 0; i < shape_info.second; i++)
    {
        std::pair<size_t, size_t> shape_info = _loader->readEdgeInfo();
        _builder->addEdge(shape_info.first, shape_info.second);
    }

    _loader->close();
    return _builder->getResult();
}

} // namespace uploading
