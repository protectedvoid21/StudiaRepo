#pragma once

#include <vector>
#include <map>
#include "Operation.h"

template <typename T>
class Node
{
    Node *_parent;
    Operation<T> *_operation;
    std::vector<Node *> _children;

    Node(const Node &other);

public:
    Node(Operation<T> *operation);
    ~Node();
    Node *addChild(Node *child);
    Node *getParent() const;
    void insertChild(int index, Node *node);
    std::vector<Node<T> *> getChildren() const;
    T evaluate(const std::map<std::string, T> &variables);
    Operation<T> *getOperation() const;
};

#include "Node.cpp"