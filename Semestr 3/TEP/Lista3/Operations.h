#include "Operation.h"
#include <cmath>

struct InitOperation : public Operation
{
    int getParameterCount() const
    {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return parameters[0];
    }

    OperationType getType() const
    {
        return FUNCTION;
    }

    std::string getName() const
    {
        return "";
    }

    bool validate(const std::vector<Operation *> operations) const
    {
        return true;
    }
};

struct FunctionOperation : public Operation
{
    bool validate(const std::vector<Operation *> operations) const
    {
        return operations.size() == getParameterCount();
    }

    OperationType getType() const
    {
        return FUNCTION;
    }

    std::string getName() const
    {
        return "";
    }
};

struct CompositeOperation : public Operation
{
    OperationType getType() const
    {
        return COMPOSITE;
    }

    std::string getName() const
    {
        return "";
    }
};

struct HashOperation : public CompositeOperation
{
    bool validate(const std::vector<Operation *> operations) const
    {
        if (operations.size() != getParameterCount())
        {
            return false;
        }
        return operations[0]->getType() == VARIABLE && operations[1]->getType() == CONSTANT;
    }

    int getParameterCount() const
    {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return parameters[0] + parameters[1];
    }
};

struct ConstantOperation : public Operation
{
private:
    int _value;
public:
    ConstantOperation(int value)
    {
        _value = value;
    }
    
    bool validate(const std::vector<Operation *> operations) const
    {
        return true;
    }

    int getParameterCount() const
    {
        return 0;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return _value;
    }

    std::string getName() const
    {
        return "";
    }

    OperationType getType() const
    {
        return CONSTANT;
    }
};

struct VariableOperation : public FunctionOperation
{
private:
    std::string _name;
public:
    VariableOperation(std::string name)
    {
        _name = name;
    }

    std::string getName() const
    {
        return _name;
    }

    int getParameterCount() const
    {
        return 0;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return parameters[0];
    }

    OperationType getType() const
    {
        return VARIABLE;
    }
};

struct AddOperation : public FunctionOperation
{
    int getParameterCount() const
    {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return parameters[0] + parameters[1];
    }
};

struct SubtractOperation : public FunctionOperation
{

    int getParameterCount() const
    {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return parameters[0] - parameters[1];
    }
};

struct MultiplyOperation : public FunctionOperation
{
    int getParameterCount() const
    {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return parameters[0] * parameters[1];
    }
};

struct DivideOperation : public FunctionOperation
{
    int getParameterCount() const
    {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return parameters[0] / parameters[1];
    }
};

struct SinOperation : public FunctionOperation
{
    int getParameterCount() const
    {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return sin(parameters[0]);
    }
};

struct CosOperation : public FunctionOperation
{
    int getParameterCount() const
    {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const
    {
        return cos(parameters[0]);
    }
};