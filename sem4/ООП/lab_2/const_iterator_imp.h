#ifndef CONST_ITERATOR_IMP_H
#define CONST_ITERATOR_IMP_H

#include "const_iterator.h"

template<typename T>
const T& IteratorConst<T>::operator *() const
{
    return *(this->ptr);
}

template<typename T>
const T* IteratorConst<T>::operator ->() const
{
    return this->ptr;
}

template<typename T>
IteratorConst<T>::IteratorConst(const IteratorConst &iter) : iterator<T> (iter.ptr) {}

template<typename T>
IteratorConst<T>::IteratorConst(T *ptr) : iterator<T> (ptr) {}

#endif // CONST_ITERATOR_IMP_H
