#include "composition.h"

namespace objects {

void Composition::add(std::shared_ptr<Object> object) {
    _objects.push_back(object);
}

void Composition::remove(size_t ind) {
    auto iterator = _objects.begin();
    std::advance(iterator, ind);
    _objects.erase(iterator);
}

std::vector<std::shared_ptr<Object> > Composition::getObjects() {
    return _objects;
}

void Composition::transform(const std::shared_ptr<math::Matrix> matrix) {
    for (auto &obj: _objects) {
        obj->transform(matrix);
    }
}

void Composition::accept(std::shared_ptr<Visitor> visitor) {
    visitor->visit(*this);
    for (auto &obj: _objects) {
        obj->accept(visitor);
    }
}

ssize_t Composition::getIndex(std::shared_ptr<Object> obj) {
    for (size_t i = 0; i < _objects.size(); i++) {
        if (obj == _objects[i]) {
            return i;
        }
    }

    return -1;
}

} // namespace objects


