#pragma once

#include <vector>
#include <map>
#include "Operation.h"

class Node {
    Node *_parent;
    Operation *_operation;
    std::vector<Node *> _children;

    Node(const Node &other);

public:
    Node(Operation *operation);
    Node *addChild(Node *child);
    std::vector<Node *> getChildren() const;
    double evaluate(const std::map<std::string, double> &variables);
    Operation *getOperation() const;
};