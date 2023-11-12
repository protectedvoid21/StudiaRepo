#include <string>
#include <vector>
#include <map>
#include "Node.h"
#include "Operation.h"

class Tree {
    Node *_root;
    std::map<std::string, Operation *> _operations;

    bool isOperation(const std::string& text);
    
    void parseToTree(std::string textInput);

public:
    Tree(const std::string& textInput, const std::map<std::string, Operation *>& operations);

    double evaluate(const std::map<std::string, double> &variables);

    void createBranch(std::vector<std::string> words, Node *parent, Operation *operation);
};