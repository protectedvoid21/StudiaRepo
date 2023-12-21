#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Node.h"
#include "Operations.h"
#include "TreeBuildResult.h"

template <typename T>
class Tree
{
private:
    Node<T> *_root;
    std::map<std::string, Operation<T> *> _operations;
    std::vector<std::string> _inputTokens;

    bool isOperation(const std::string &text);
    TreeBuildResult createBranch(std::vector<std::string> &words, Node<T> *parent, Operation<T> *operation, TreeBuildResult &result);
public:
    Tree(const std::vector<std::string> &tokens, const std::map<std::string, Operation<T> *> &operations);
    Tree(const Tree<T> &otherTree);
    Tree(Tree<T> &&otherTree);
    ~Tree();
    TreeBuildResult buildTree();
    TreeBuildResult join(const std::vector<std::string> &tokens);
    T evaluate(const std::map<std::string, T> &variables);
    std::set<std::string> getVariables() const;
    std::string print() const;

    Tree operator+(Tree &&other);
    Tree operator=(Tree &&other);
};

#include "Tree.cpp"