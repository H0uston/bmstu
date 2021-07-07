#ifndef SET_H
#define SET_H
#pragma once


#include <iostream>
#include <ostream>
#include <memory>
#include "base_container.h"
#include "exception.h"
#include "make_unique.h"
#include "set_iterator.h"

template <typename T>
class Set : public container_core::base_container
{
public:
    Set();
    Set(int num, ...);
    Set(const T *arr, size_t num);
    Set(std::initializer_list<T> lst);
    explicit Set(const Set<T>& set) = default;
    Set(Set<T>&& set) noexcept;

    ~Set();

    Set<T>& operator =(const Set<T> &another_set);
    Set<T>& operator =(Set<T>&& another_set);
    Set<T>& operator =(const std::initializer_list<T>& list);

    Set<T>& add(const T& elem);
    Set<T>& operator +=(const T& elem);
    Set<T>& operator ,(const T& elem);
    Set<T> operator +(const T& elem) const;
    Set<T> operator +(ConstIterator<T>& iter) const;
    Set<T>& operator ,(ConstIterator<T>& iter);


    Set<T>& remove(const T& elem);
    Set<T>& operator -=(const T& elem);
    Set<T> operator -(const T& elem) const;
    Set<T>& remove(ConstIterator<T>& iter);
    Set<T>& operator -=(ConstIterator<T>& iter);
    Set<T> operator -(ConstIterator<T>& iter) const;

    bool in(const T& elem) const;
    bool in(const ConstIterator<T>& iter) const;
    bool operator <(const T& elem) const;
    bool operator <(const ConstIterator<T>& iter) const;
    bool operator ==(const Set<T>& another_set) const;
    bool operator !=(const Set<T>& another_set) const;

    Set<T> compound(const Set<T>& another_set) const;
    Set<T> compound(const T& elem) const;
    Set<T>& append(const Set<T>& another_set);
    Set<T> difference(const Set<T>& another_set) const;
    Set<T> difference(const T& elem) const;
    Set<T> crossing(const Set<T>& another_set) const;
    Set<T> symmetric_difference(const Set<T>& another_set) const;

    template<typename _T>
    friend std::ostream& operator <<(std::ostream& os, const Set<_T>& set);

    size_t power() const;

    Set<T> operator +(const Set<T>& another_set) const;
    Set<T> operator -(const Set<T>& another_set) const;
    Set<T> operator &(const Set<T>& another_set) const;
    Set<T> operator ^(const Set<T>& another_set) const;

    Set<T>& operator +=(const Set<T>& another_set);
    Set<T>& operator -=(const Set<T>& another_set);
    Set<T>& operator &=(const Set<T>& another_set);
    Set<T>& operator ^=(const Set<T>& another_set);

    Set<T>& clear();

    ConstIterator<T> inititalizeIterator() const;
private:
    size_t size;
    std::shared_ptr<std::shared_ptr<T>> data;
};


#endif // SET_H


