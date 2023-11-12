#include "Operation.h"
#include <cmath>

struct InitOperation : public Operation {
    int getParameterCount() const {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0];
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
};

struct VariableOperation : public Operation {
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
};

struct AddOperation : public Operation {
    int getParameterCount() const {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0] + parameters[1];
    }
};

struct SubtractOperation : public Operation {

    int getParameterCount() const {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0] - parameters[1];
    }
};

struct MultiplyOperation : public Operation {
    int getParameterCount() const {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0] * parameters[1];
    }
};

struct DivideOperation : public Operation {
    int getParameterCount() const {
        return 2;
    }

    double execute(const std::vector<double> &parameters) const {
        return parameters[0] / parameters[1];
    }
};

struct SinOperation : public Operation {
    int getParameterCount() const {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const {
        return sin(parameters[0]);
    }
};

struct CosOperation : public Operation {
    int getParameterCount() const {
        return 1;
    }

    double execute(const std::vector<double> &parameters) const {
        return cos(parameters[0]);
    }
};