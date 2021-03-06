#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <vector>
#include "object.h"

namespace objects {

class Composition: public Object {
public:
    Composition() = default;

    void add(std::shared_ptr<Object> obj);
    void remove(size_t ind);
    ssize_t getIndex(std::shared_ptr<Object> obj);

    std::vector<std::shared_ptr<Object>> getObjects();

    void transform(const std::shared_ptr<Matrix> matrix) override;
    void accept(std::shared_ptr<Visitor> visitor) override;
private:
    std::vector<std::shared_ptr<Object>> _objects;
};

}
#endif
