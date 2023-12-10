#pragma once

#include <string>
#include <vector>

enum OperationType
{
    CONSTANT,
    VARIABLE,
    FUNCTION,
};

template <typename T>
struct Operation
{
    virtual T execute(const std::vector<T> &parameters) const = 0;
    virtual int getParameterCount() const = 0;
    virtual std::string getName() const = 0;
    virtual OperationType getType() const = 0;
};