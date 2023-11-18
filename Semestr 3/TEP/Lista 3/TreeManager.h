#pragma once
#include <string>
#include "TextUtils.h"
#include "Tree.h"
#include <iostream>

class TreeManager {
private:
    Tree *_tree;
    std::map<std::string, Operation *> _operations;
    
public:
    TreeManager(const std::map<std::string, Operation *> &operations);
    void getInput(const std::string &textInput);
    void getVariables() const;
    void print() const;
    void createTree(std::vector<std::string> &tokens);
    void join(std::vector<std::string> &tokens);
    void compute(std::vector<std::string> &tokens);
};