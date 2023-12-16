#pragma once
#include "Operation.h"
#include <cmath>

template <typename T>
struct InitOperation : public Operation<T>
{
    int getParameterCount() const
    {
        return 1;
    }

    T execute(const std::vector<T> &parameters) const
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
};

template <typename T>
struct FunctionOperation : public Operation<T>
{
    OperationType getType() const
    {
        return FUNCTION;
    }

    std::string getName() const
    {
        return "";
    }
};

template <typename T>
struct ConstantOperation : public Operation<T>
{
private: 
    T _value;
public:
    ConstantOperation(T value)
    {
        _value = value;
    }

    int getParameterCount() const
    {
        return 0;
    }

    T execute(const std::vector<T> &parameters) const
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

template <typename T>
struct VariableOperation : public FunctionOperation<T>
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

    T execute(const std::vector<T> &parameters) const
    {
        return parameters[0];
    }

    OperationType getType() const
    {
        return VARIABLE;
    }
};

template <typename T>
struct AddOperation : public FunctionOperation<T>
{
    int getParameterCount() const
    {
        return 2;
    }

    T execute(const std::vector<T> &parameters) const
    {
        return parameters[0] + parameters[1];
    }
};

template <typename T>
struct SubtractOperation : public FunctionOperation<T>
{

    int getParameterCount() const
    {
        return 2;
    }

    T execute(const std::vector<T> &parameters) const
    {
        return parameters[0] - parameters[1];
    }
};

template <typename T>
struct MultiplyOperation : public FunctionOperation<T>
{
    int getParameterCount() const
    {
        return 2;
    }

    T execute(const std::vector<T> &parameters) const
    {
        return parameters[0] * parameters[1];
    }
};

template <typename T>
struct DivideOperation : public FunctionOperation<T>
{
    int getParameterCount() const
    {
        return 2;
    }

    T execute(const std::vector<T> &parameters) const
    {
        return parameters[0] / parameters[1];
    }
};

template <typename T>
struct SinOperation : public FunctionOperation<T>
{
    int getParameterCount() const
    {
        return 1;
    }

    T execute(const std::vector<T> &parameters) const
    {
        return sin(parameters[0]);
    }
};

template <typename T>
struct CosOperation : public FunctionOperation<T>
{
    int getParameterCount() const
    {
        return 1;
    }

    T execute(const std::vector<T> &parameters) const
    {
        return cos(parameters[0]);
    }
};

// Specializations for std::string

template<>
struct AddOperation<std::string> : public Operation<std::string>
{
    int getParameterCount() const
    {
        return 2;
    }

    std::string execute(const std::vector<std::string> &parameters) const
    {
        return parameters[0] + parameters[1];
    }

    OperationType getType() const
    {
        return FUNCTION;
    }

    std::string getName() const
    {
        return "+";
    }
};

template<>
struct SubtractOperation<std::string> : public Operation<std::string>
{
    int getParameterCount() const
    {
        return 2;
    }

    std::string execute(const std::vector<std::string> &parameters) const
    {
        std::string text = parameters[0];
        std::string toRemove = parameters[1];

        size_t position = text.rfind(toRemove);

        if (position != std::string::npos && position == text.length() - toRemove.length())
        {
            return text.substr(0, position);
        }
        return text;
    }

    OperationType getType() const
    {
        return FUNCTION;
    }

    std::string getName() const
    {
        return "-";
    }
};

template<>
struct MultiplyOperation<std::string> : public Operation<std::string>
{
    int getParameterCount() const
    {
        return 2;
    }

    std::string execute(const std::vector<std::string> &parameters) const
    {
        std::string text = parameters[0];
        std::string multiplierText = parameters[1];

        if (multiplierText.empty())
        {
            return text;
        }

        std::string result = text;

        size_t pos = result.find(multiplierText[0]);
        while (pos != std::string::npos)
        {
            result.replace(pos, 1, multiplierText);
            pos = result.find(multiplierText[0], pos + multiplierText.length() - 1);
        }

        return result;
    }

    OperationType getType() const
    {
        return FUNCTION;
    }

    std::string getName() const
    {
        return "*";
    }
};

template<>
struct DivideOperation<std::string> : public Operation<std::string>
{
    int getParameterCount() const
    {
        return 2;
    }

    std::string execute(const std::vector<std::string> &parameters) const
    {
        std::string text = parameters[0];
        std::string dividerText = parameters[1];

        if (dividerText.empty())
        {
            return text;
        }

        std::string result = text;

        size_t pos = result.find(dividerText);
        while (pos != std::string::npos)
        {
            result.erase(pos + 1, dividerText.length() - 1);
            pos = result.find(dividerText, pos + 1);
        }

        return result;
    }

    OperationType getType() const
    {
        return FUNCTION;
    }

    std::string getName() const
    {
        return "/";
    }
};

//specializations for bool

template <>
struct AddOperation<bool> : public Operation<bool>
{
    int getParameterCount() const
    {
        return 2;
    }

    bool execute(const std::vector<bool> &parameters) const
    {
        return parameters[0] || parameters[1];
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

template <>
struct SubtractOperation<bool> : public Operation<bool>
{
    int getParameterCount() const
    {
        return 2;
    }

    bool execute(const std::vector<bool> &parameters) const
    {
        return parameters[0] && !parameters[1];
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

template <>
struct MultiplyOperation<bool> : public Operation<bool>
{
    int getParameterCount() const
    {
        return 2;
    }

    bool execute(const std::vector<bool> &parameters) const
    {
        return parameters[0] && parameters[1];
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

template <>
struct DivideOperation<bool> : public Operation<bool>
{
    int getParameterCount() const
    {
        return 2;
    }

    bool execute(const std::vector<bool> &parameters) const
    {
        return parameters[0] || !parameters[1];
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