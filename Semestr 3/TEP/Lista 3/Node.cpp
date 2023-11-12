#include "Node.h"
#include "Operations.h"

Node::Node(Operation* operation) : _operation(operation) {}

Node::Node(const Node &other) {
    _operation = other._operation;
    _parent = other._parent;
    _children = other._children;
}

double Node::evaluate(const std::map<std::string, double> &variables) {
    if (_operation->getParameterCount() == 0) {
        VariableOperation* variableOperation = dynamic_cast<VariableOperation *>(_operation);
        if (variableOperation != nullptr) {
            return variables.at(variableOperation->getName());
        }
        return _operation->execute(std::vector<double>());
    }
    
    std::vector<double> childResults;
    childResults.reserve(_children.size());

    for (Node *child : _children) {
        childResults.push_back(child->evaluate(variables));
    }
    
    return _operation->execute(childResults);
}

Node *Node::addChild(Node *child) {
    _children.push_back(child);
    child->_parent = this;
    return child;
}