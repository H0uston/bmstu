#ifndef SET_ITERATOR_IMP_H
#define SET_ITERATOR_IMP_H

#include "set_iterator.h"
#include <memory>

template <class T>
ConstIterator<T>::ConstIterator(): BaseIterator<T>() {}

template <class T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<T>& address, size_t size): BaseIterator<T>(address, size) {}

template <class T>
ConstIterator<T>::ConstIterator (const ConstIterator<T> &other): BaseIterator<T>(other) {}

template <class T>
const T& ConstIterator<T>::operator *() const
{
    return *(this->actual_address());
}

template <class T>
const T* ConstIterator<T>:: operator ->()
{
    return this->actual_address();
}


#endif // SET_ITERATOR_IMP_H
