#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <memory>

template <class T>
class BaseIterator
{
public:
    BaseIterator() = default;
    BaseIterator(const std::shared_ptr<T>& address, size_t size);
    BaseIterator(const BaseIterator<T> &other);

    bool check() const;

    BaseIterator& operator ++();
    BaseIterator& operator --();
    BaseIterator operator ++(int);
    BaseIterator operator --(int);
    ptrdiff_t operator -(const BaseIterator<T> &other) const;

    template <class Type>
    friend bool operator == (const BaseIterator<Type> &it1, const BaseIterator<Type> &it2);

    template <class Type>
    friend bool operator != (const BaseIterator<Type> &it1, const BaseIterator<Type> &it2);


protected:
    std::weak_ptr<T> address;
    size_t size;
    size_t index;
    T* actual_address() const;
};

#include "iterator_imp.h"


#endif // ITERATOR_H
