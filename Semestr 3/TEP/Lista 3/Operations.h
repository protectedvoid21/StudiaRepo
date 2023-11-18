#include "Operation.h"
#include <cmath>

struct InitOperation : public Operation {
    int getParameterCount() const {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0];
    }
    
    OperationType getType() const {
        return FUNCTION;
    }
    
    std::string getName() const {
        return "";
    }
};

struct FunctionOperation : public Operation {
    OperationType getType() const {
        return FUNCTION;
    }
    
    std::string getName() const {
        return "";
    }
};

struct ConstantOperation : public Operation {
private:
    int _value;
public:
    ConstantOperation(int value) {
        _value = value;
    }

    int getParameterCount() const {
        return 0;
    }

    double execute(const std::vector<double> &parameters) const {
        return _value;
    }
    
    std::string getName() const {
        return "";
    }
    
    OperationType getType() const {
        return CONSTANT;
    }
};

struct VariableOperation : public FunctionOperation {
private:
    std::string _name;
public:
    VariableOperation(std::string name) {
        _name = name;
    }
    
    std::string getName() const {
        return _name;
    }
    
    int getParameterCount() const {
        return 0;
    }
    
    double execute(const std::vector<double> &parameters) const {
        return parameters[0];
    }
    
    OperationType getType() const {
        return VARIABLE;
    }
};

struct AddOperation : public FunctionOperation {
    int getParameterCount() const {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0] + parameters[1];
    }
};

struct SubtractOperation : public FunctionOperation {

    int getParameterCount() const {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0] - parameters[1];
    }
};

struct MultiplyOperation : public FunctionOperation {
    int getParameterCount() const {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0] * parameters[1];
    }
};

struct DivideOperation : public FunctionOperation {
    int getParameterCount() const {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0] / parameters[1];
    }
};

struct SinOperation : public FunctionOperation {
    int getParameterCount() const {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const {
        return sin(parameters[0]);
    }
};

struct CosOperation : public FunctionOperation {
    int getParameterCount() const {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const {
        return cos(parameters[0]);
    }
};