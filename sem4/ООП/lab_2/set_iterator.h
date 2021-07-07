#ifndef SET_ITERATOR_H
#define SET_ITERATOR_H

#include "exception.h"
#include "iterator.h"

template <class T>
class ConstIterator: public BaseIterator<T>
{
public:
    ConstIterator();
    ConstIterator(const std::shared_ptr<T>& address, size_t size);
    ConstIterator(const ConstIterator &other);
    const T& operator * () const;
    const T* operator -> ();
};

#include "set_iterator_imp.h"

#endif // SET_ITERATOR_H
