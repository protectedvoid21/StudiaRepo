#include "Node.h"
#include "Operations.h"

Node::Node(Operation *operation) : _operation(operation)
{
}

Node::Node(const Node &other)
{
    _operation = other._operation;
    _parent = other._parent;
    _children = other._children;
}

Node::~Node()
{
    for (Node *child : _children)
    {
        delete child;
    }
}

double Node::evaluate(const std::map<std::string, double> &variables)
{
    if (_operation->getType() == OperationType::CONSTANT)
    {
        return _operation->execute(std::vector<double>());
    }
    if (_operation->getType() == OperationType::VARIABLE)
    {
        return variables.at(_operation->getName());
    }

    std::vector<double> childResults;
    childResults.reserve(_children.size());

    for (Node *child : _children)
    {
        childResults.push_back(child->evaluate(variables));
    }

    return _operation->execute(childResults);
}

Node *Node::addChild(Node *child)
{
    _children.push_back(child);
    child->_parent = this;
    return child;
}

Operation *Node::getOperation() const
{
    return _operation;
}

std::vector<Node *> Node::getChildren() const
{
    return _children;
}

Node *Node::getParent() const
{
    return _parent;
}

void Node::insertChild(int index, Node *node)
{
    if (index < 0 || index >= _children.size())
    {
        return;
    }

    _children[index] = node;
}

