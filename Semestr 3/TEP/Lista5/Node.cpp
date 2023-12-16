#include <map>
#include "Node.h"

template <typename T>
Node<T>::Node(Operation<T> *operation) : _operation(operation)
{
}

template <typename T>
Node<T>::Node(const Node<T> &other)
{
    _operation = other._operation;
    _parent = other._parent;
    _children = other._children;
}

template <typename T>
Node<T>::~Node()
{
    for (Node *child : _children)
    {
        delete child;
    }
}

template <typename T>
T Node<T>::evaluate(const std::map<std::string, T> &variables)
{
    if (_operation->getType() == OperationType::CONSTANT)
    {
        return _operation->execute(std::vector<T>());
    }
    if (_operation->getType() == OperationType::VARIABLE)
    {
        return variables.at(_operation->getName());
    }

    std::vector<T> childResults;

    for (Node *child : _children)
    {
        childResults.push_back(child->evaluate(variables));
    }

    return _operation->execute(childResults);
}

template <typename T>
Node<T> *Node<T>::addChild(Node<T> *child)
{
    _children.push_back(child);
    child->_parent = this;
    return child;
}

template <typename T>
Operation<T> *Node<T>::getOperation() const
{
    return _operation;
}

template<typename T>
std::vector<Node<T> *> Node<T>::getChildren() const
{
    return _children;
}

template <typename T>
Node<T> *Node<T>::getParent() const
{
    return _parent;
}

template <typename T>
void Node<T>::insertChild(int index, Node *node)
{
    if (index < 0 || index >= _children.size())
    {
        return;
    }

    _children[index] = node;
}