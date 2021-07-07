#ifndef VISITOR_H
#define VISITOR_H

namespace objects {

class Shape;
class Camera;
class Composition;

class Visitor {
public:
    Visitor() = default;
    virtual ~Visitor() = default;

    virtual void visit(Camera &camera) = 0;
    virtual void visit(Shape &model) = 0;
    virtual void visit(Composition &composite) = 0;
};

}

#endif
