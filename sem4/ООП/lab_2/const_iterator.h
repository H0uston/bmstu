#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include "iterator.h"

template <typename T>
class IteratorConst: public iterator<T>
{
public:
    IteratorConst(const IteratorConst<T>&);

    const T& operator *() const;
    const T* operator ->() const;

    IteratorConst(T*);
};

#endif // CONST_ITERATOR_H
