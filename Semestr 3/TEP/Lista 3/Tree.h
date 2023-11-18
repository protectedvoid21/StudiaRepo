#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Node.h"
#include "TreeBuildResult.h"

class Tree {
    Node *_root;
    std::map<std::string, Operation *> _operations;
    std::vector<std::string> _inputTokens;
    
    bool isOperation(const std::string &text);
    TreeBuildResult createBranch(std::vector<std::string> &words, Node *parent, Operation *operation, TreeBuildResult &result);
public:
    Tree(const std::vector<std::string> &tokens, const std::map<std::string, Operation *> &operations);
    TreeBuildResult buildTree();
    double evaluate(const std::map<std::string, double> &variables);
    std::set<std::string> getVariables() const;
    std::string print() const;
};