#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class base_exception : public std::exception
{
public:
    base_exception(std::string filename, std::string classname, int line, std::string info)
    {
        std::string str_err_info = "filename: " + filename + "\nclass name: " + classname + "\nline: " + std::to_string(line)
            + "\ninfo: " + info;
        err_info = str_err_info.c_str();
    }
    const char* what() const noexcept override
    {
        return this->err_info;
    }
protected:
    const char* err_info;
};

class memory_allocate_exception : public base_exception
{
public:
    memory_allocate_exception(std::string filename, std::string classname, int line, std::string info)
        : base_exception(filename, classname, line, info) {}
    const char* what() const noexcept override
    {
        return this->err_info;
    }
};

class set_size_exception : public base_exception
{
public:
    set_size_exception(std::string filename, std::string classname, int line, std::string info)
        : base_exception(filename, classname, line, info) {}
    const char* what() const noexcept override
    {
        return this->err_info;
    }
};

class set_iterator_exception : public base_exception
{
public:
    set_iterator_exception(std::string filename, std::string classname, int line, std::string info)
        : base_exception(filename, classname, line, info) {}
    const char* what() const noexcept override
    {
        return this->err_info;
    }
};

#endif // EXCEPTION_H
