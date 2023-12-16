#pragma once

#include <string>
#include "TextUtils.h"
#include "Tree.h"
#include <iostream>

template <typename T>
class TreeManager
{
private:
    Tree<T> *_tree;
    std::map<std::string, Operation<T> *> _operations;

public:
    TreeManager(const std::map<std::string, Operation<T> *> &operations);
    void getInput(const std::string &textInput);
    void getVariables() const;
    void print() const;
    void createTree(std::vector<std::string> &tokens);
    void join(std::vector<std::string> &tokens);
    void compute(std::vector<std::string> &tokens);
    T extractValue(const std::string &text) const;
    
    const std::string ENTER_COMMAND = "enter";
    const std::string PRINT_COMMAND = "print";
    const std::string VARS_COMMAND = "vars";
    const std::string JOIN_COMMAND = "join";
    const std::string COMP_COMMAND = "comp";
};

#include "TreeManager.cpp"