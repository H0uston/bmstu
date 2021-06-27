#ifndef TREE_H
#define TREE_H

#include "config.h"
#include "model.h"

class Tree : public Model
{
public:
    Tree(Model& model);

private:
    QColor color_trunk = HORSE_SEAT;
    QColor color_leaf = LEAF
};

#endif // TREE_H
