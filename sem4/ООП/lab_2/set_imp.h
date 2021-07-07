#ifndef SET_IMP_H
#define SET_IMP_H

#include "set.h"
#include <memory>

template <typename T>
Set<T>::Set()
{
    this->size = 0;
    this->elements_count = 0;
    this->data = nullptr;
}

template <typename T>
Set<T>::Set(int num, ...)
{
    va_list arg;
    va_start(arg, num);
    this->size = 0;
    this->elements_count = 0;
    this->data = nullptr;

    try
    {
        this->data = std::make_shared<std::shared_ptr<T>>(std::shared_ptr<T>(new T[this->size]));
    }
    catch(std::bad_alloc)
    {
        throw memory_allocate_exception(__FILE__, typeid(*this).name(), __LINE__, "Memory error!");
    }

    T elem;
    for ( ; num; --num)
    {
        elem = va_arg(arg, T);
        this->add(elem);
    }

    va_end(arg);
}

template<typename T>
Set<T>::Set(const T *arr, size_t num)
{
    this->size = 0;
    this->elements_count = 0;
    this->data = nullptr;
    try
    {
        this->data = std::make_shared<std::shared_ptr<T>>(std::shared_ptr<T>(new T[this->size]));
    }
    catch(std::bad_alloc)
    {
        throw memory_allocate_exception(__FILE__, typeid(*this).name(), __LINE__, "Memory error!");
    }

    for (unsigned int i = 0; i < num; i++)
        this->add(arr[i]);
}

template<typename T>
Set<T>::Set(std::initializer_list<T> lst):base_container()
{
    this->size = 0;
    this->elements_count = 0;
    this->data = nullptr;
    auto iter = lst.begin();

    for ( ; iter != lst.end(); ++iter)
    {
        this->add(*iter);
    }
}

template<typename T>
Set<T>::Set(Set<T>&& set) noexcept
{
    this->size = set.size;
    this->data = std::move(set.data);
    set.size = 0;
}

template <typename T>
Set<T>& Set<T>::add(const T& elem)
{
    if (this->in(elem))
    {
        return *this;
    }

    this->size += 1;
    auto newData = std::make_shared<std::shared_ptr<T>>(std::shared_ptr<T>(new T[this->size]));
    for (unsigned int i = 0; i < this->power(); i++)
        newData.get()->get()[i] = 0;

    if (!newData)
        throw memory_allocate_exception(__FILE__, typeid(*this).name(), __LINE__, "Memory error!");

    for (unsigned int i = 0; i < this->power() - 1; i++)
        newData.get()->get()[i] = data.get()->get()[i];
    newData.get()->get()[this->power() - 1] = elem;

    data = std::move(newData);

    return *this;
}

template<typename T>
Set<T>& Set<T>::remove(const T& elem)
{
    if (this->is_empty())
        throw set_size_exception(__FILE__, typeid(*this).name(), __LINE__, "Set is empty!");

    if (!this->in(elem))
        return *this;

    this->size -= 1;
    auto newData = std::make_shared<std::shared_ptr<T>>(std::shared_ptr<T>(new T[this->size]));

    for (unsigned int i = 0; i < this->power(); i++)
        newData.get()[i] = 0;

    unsigned int index = 0;
    for (unsigned int i = 0; i < this->power() + 1; i++)
        if (elem == data.get()->get()[i])
        {
            index = i;
            break;
        }

    for (unsigned int i = 0; i < index; i++)
        newData.get()->get()[i] = data.get()->get()[i];

    for (unsigned int i = index; i < this->power(); i++)
        newData.get()->get()[i] = data.get()->get()[i + 1];

    data = std::move(newData);

    return *this;
}

template<typename T>
Set<T>& Set<T>::remove(ConstIterator<T>& iter)
{
    if (this->is_empty())
        throw set_size_exception(__FILE__, typeid(*this).name(), __LINE__, "Set is empty!");

    if (!this->in(*iter))
        return *this;

    this->size -= 1;
    auto newData = std::make_shared<std::shared_ptr<T>>(std::shared_ptr<T>(new T[this->size]));

    for (unsigned int i = 0; i < this->power(); i++)
        newData.get()[i] = 0;

    unsigned int index = 0;
    for (unsigned int i = 0; i < this->power() + 1; i++)
        if (*iter == data.get()->get()[i])
        {
            index = i;
            break;
        }

    for (unsigned int i = 0; i < index; i++)
        newData.get()->get()[i] = data.get()->get()[i];

    for (unsigned int i = index; i < this->power(); i++)
        newData.get()->get()[i] = data.get()->get()[i + 1];

    data = std::move(newData);

    return *this;
}

template<typename T>
bool Set<T>::in(const T& elem) const
{
    for (size_t i = 0; i < this->elements_count; i++)
    {
        if (this->data.get()->get()[i] == elem)
            return true;
    }
    return false;
}

template<typename T>
bool Set<T>::in(const ConstIterator<T>& iter) const
{
    for (size_t i = 0; i < this->elements_count; i++)
    {
        if (this->data.get()->get()[i] == *iter)
            return true;
    }
    return false;
}

template<typename T>
bool Set<T>::operator <(const T& elem) const
{
    return this->in(elem);
}

template<typename T>
bool Set<T>::operator <(const ConstIterator<T>& iter) const
{
    return this->in(*iter);
}

template<typename T>
bool Set<T>::operator ==(const Set<T>& another_set) const
{
    if (*this == *another_set)
        return true;

    if (this->power() != another_set->power())
        return false;

    for (size_t i = 0; this->power(); i++)
    {
        if (*(this->data.get()[i]) != *(another_set->data.get()[i]))
            return false;
    }

    return true;
}

template<typename T>
bool Set<T>::operator !=(const Set<T>& another_set) const
{
    if (*this == *another_set)
        return false;

    if (this->power() != another_set->power())
        return true;

    for (size_t i = 0; this->power(); i++)
    {
        if (*(this->data.get()[i]) != *(another_set->data.get()[i]))
            return true;
    }

    return false;
}

template <typename T>
Set<T>::~Set()
{
    this->data.reset();
    this->size = 0;
}

template <typename T>
Set<T> Set<T>::compound(const Set<T>& another_set) const
{
    Set<T> tmp;

    for (size_t i = 0; i < this->power(); i++)
    {
        tmp.add(this->data.get()->get()[i]);
    }

    for (size_t i = 0; i < another_set.power(); i++)
    {
        tmp.add(another_set.data.get()->get()[i]);
    }

    return tmp;
}

template <typename T>
Set<T>& Set<T>::append(const Set<T>& another_set)
{
    for (size_t i = 0; i < another_set.power(); i++)
    {
        this->add(another_set.data.get()->get()[i]);
    }

    return *this;
}

template <typename T>
Set<T> Set<T>::compound(const T& elem) const
{
    Set<T> tmp;

    for (size_t i = 0; i < this->power(); i++)
    {
        tmp.add(this->data.get()->get()[i]);
    }

    tmp.add(elem);
    return tmp;
}

template<typename T>
Set<T> Set<T>::difference(const Set<T>& another_set) const
{
    Set<T> tmp;

    tmp.compound(*this);

    for (size_t i = 0; i < tmp.power(); i++)
    {
        if (another_set.in(tmp.data.get()->get()[i]))
        {
            tmp.remove(tmp.data.get()->get()[i]);
            i--;
        }
    }

    return tmp;
}

template <typename T>
Set<T> Set<T>::difference(const T& elem) const
{
    Set<T> tmp;
    tmp.compound(this);
    tmp->remove(elem);

    return tmp;
}

template<typename T>
Set<T> Set<T>::crossing(const Set<T>& another_set) const
{
    Set<T> tmp;

    tmp.compound(*this);

    for (size_t i = 0; i < tmp.power(); i++)
    {
        if (!another_set.in(tmp.data.get()->get()[i]))
        {
            tmp.remove(tmp.data.get()->get()[i]);
            i--;
        }
    }

    return tmp;
}

template<typename T>
Set<T> Set<T>::symmetric_difference(const Set<T>& another_set) const
{
    Set<T> tmp_1;
    Set<T> tmp_2;
    Set<T> tmp_3;

    tmp_1.compound(*this);
    tmp_2.compound(tmp_1);

    tmp_2.crossing(another_set);

    tmp_1.compound(another_set);
    tmp_1.difference(tmp_2);

    return tmp_1;
}


template<typename _T>
std::ostream& operator <<(std::ostream& stream, const Set<_T>& set)
{
    for (size_t i = 0; i < set.power(); i++)
        stream << set.data.get()->get()[i] << " ";
    stream << std::endl;
    return stream;
}

template<typename T>
Set<T>& Set<T>::operator +=(const Set<T> &another_set)
{
    this->compound(another_set);
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator +=(const T& elem)
{
    this->add(elem);
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator -=(const Set<T> &another_set)
{
    if (this->is_empty())
    {
        throw set_size_exception(__FILE__, typeid(*this).name(), __LINE__, "Set is empty!");
    }
    else
    {
        this->difference(another_set);
    }

    return *this;
}

template<typename T>
Set<T>& Set<T>::operator -=(const T& elem)
{
    this->remove(elem);
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator -=(ConstIterator<T>& iter)
{
    this->remove(*iter);
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator &=(const Set<T> &another_set)
{
    if (this->is_empty())
    {
        throw set_size_exception(__FILE__, typeid(*this).name(), __LINE__, "Set is empty!");
    }
    else
    {
        this->crossing(another_set);
    }

    return *this;
}

template<typename T>
Set<T>& Set<T>::operator ^=(const Set<T> &another_set)
{
    if (this->is_empty())
    {
        throw set_size_exception(__FILE__, typeid(*this).name(), __LINE__, "Set is empty!");
    }
    else
    {
        this->symmetric_difference(another_set);
    }

    return *this;
}

template<typename T>
Set<T> Set<T>::operator +(const Set<T> &another_set) const
{
    Set<T> tmp;
    tmp.compound(*this);
    tmp.compound(another_set);
    return tmp;
}

template<typename T>
Set<T> Set<T>::operator +(const T& elem) const
{
    Set<T> tmp;
    tmp.compound(*this);
    tmp.add(elem);
    return tmp;
}

template<typename T>
Set<T> Set<T>::operator +(ConstIterator<T>& iter) const
{
    Set<T> tmp;
    tmp.compound(*this);
    tmp.add(*iter);
    return tmp;
}

template <typename T>
Set<T>& Set<T>::operator ,(const T& elem)
{
    this->add(elem);
    return *this;
}

template<typename T>
Set<T> Set<T>::operator -(const Set<T> &another_set) const
{
    Set<T> tmp;
    tmp.compound(*this);
    tmp.difference(another_set);
    return tmp;
}

template<typename T>
Set<T> Set<T>::operator -(const T& elem) const
{
    Set<T> tmp;
    tmp.compound(*this);
    tmp.remove(elem);
    return tmp;
}

template<typename T>
Set<T> Set<T>::operator -(ConstIterator<T>& iter) const
{
    Set<T> tmp;
    tmp.compound(*this);
    tmp.remove(*iter);
    return tmp;
}

template<typename T>
Set<T> Set<T>::operator &(const Set<T> &another_set) const
{
    Set<T> tmp;
    tmp.compound(*this);
    tmp.crossing(another_set);
    return tmp;
}

template<typename T>
Set<T> Set<T>::operator ^(const Set<T> &another_set) const
{
    Set<T> tmp;
    tmp.compound(*this);
    tmp.symmetric_difference(another_set);
    return tmp;
}

template<typename T>
size_t Set<T>::power(void) const
{
    return this->size;
}

template<typename T>
Set<T>& Set<T>::operator =(const Set<T>& another_set)
{
    if (this == &another_set)
        return *this;
    Set<T> tmp;
    this->crossing(tmp);
    this->compound(another_set);
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator =(Set<T>&& another_set)
{
    if (this == &another_set)
        return *this;
    this->size = another_set.size;
    this->data = std::move(another_set.data);
    another_set.size = 0;
    return *this;
}

template<typename T>
Set<T>& Set<T>::operator =(const std::initializer_list<T>& list)
{
    this->size = list.size();
    this->data = std::shared_ptr<T>(this->size);
    if (!this->data)
    {
        throw memory_allocate_exception(__FILE__, typeid(*this).name(), __LINE__, "Memory error!");
    }

    auto iter = list.begin();
    size_t i = 0;
    while (iter != list.end())
    {
        this->data[i] = std::make_shared<T>(iter);
        iter++;
        i++;
    }
}

template<typename T>
Set<T>& Set<T>::clear()
{
    while (this->power() > 0)
    {
        this->remove(*(this->data).get()[0]);
    }

    return *this;
}

template<typename T>
ConstIterator<T> Set<T>::inititalizeIterator() const
{
    return ConstIterator<T>(*this->data.get(), this->power());
}

#endif // SET_IMP_H
