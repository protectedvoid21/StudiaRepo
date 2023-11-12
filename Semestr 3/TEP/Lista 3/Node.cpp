#include "Node.h"

Node::Node(Operation* operation) : _operation(operation) {}

Node::Node(const Node &other) {
    _operation = other._operation;
    _parent = other._parent;
    _children = other._children;
}

double Node::evaluate(const std::map<std::string, double> &variables) {
    if (_operation->getParameterCount() == 0) {
        return _operation->execute();
    }
    
    std::vector<double> childResults;
    childResults.reserve(_children.size());

    for (Node *child : _children) {
        childResults.push_back(child->evaluate(variables));
    }
    
    return _operation->execute(childResults);
}
