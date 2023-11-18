#pragma once

#include <string>
#include <vector>

enum OperationType {
    CONSTANT,
    VARIABLE,
    FUNCTION
};

struct Operation {
    virtual double execute(const std::vector<double> &parameters) const = 0;
    virtual int getParameterCount() const = 0;
    virtual std::string getName() const = 0;
    virtual OperationType getType() const = 0;
};