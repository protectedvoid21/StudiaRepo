#include <stdexcept>
#include <set>
#include "Tree.h"
#include "Operation.h"
#include "Operations.h"
#include "TextUtils.h"


Tree::Tree(const std::vector<std::string> &tokens, const std::map<std::string, Operation *> &operations) : _operations(operations) {
    _inputTokens = tokens;
    _root = new Node(new InitOperation());
}

Tree::~Tree() {
    delete _root->getChildren()[0];
}

TreeBuildResult Tree::buildTree() {
    std::vector<std::string> tokens;
    tokens.reserve(_inputTokens.size());
    
    for (const std::string &token: _inputTokens) {
        tokens.push_back(token);
    }
    TreeBuildResult result;
    result = createBranch(tokens, _root, new InitOperation(), result);

    if (!tokens.empty()) {
        std::string warningText = "Too many parameters for some operations. These parameters will be ignored:";

        for(const std::string &word: tokens) {
            warningText += " " + word;
            _inputTokens.erase(tokens.begin());
        }

        result.addWarning(warningText);
    }
    
    return result;
}

double Tree::evaluate(const std::map<std::string, double> &variables) {
    return _root->evaluate(variables);
}

bool Tree::isOperation(const std::string &text) {
    return _operations[text] != nullptr;
}

TreeBuildResult Tree::createBranch(std::vector<std::string> &words, Node *parent, Operation *operation, TreeBuildResult &result) {
    while (words.size() < operation->getParameterCount()) {
        result.addWarning("Not enough parameters for operation " + operation->getName() + " at '" + print() + "'. Adding 1 as parameter.");
        
        words.emplace_back("1");
        _inputTokens.emplace_back("1");
    }

    for (int i = 0; i < operation->getParameterCount(); i++) {
        std::string word = words.front();
        words.erase(words.begin());

        if (isNumber(word)) {
            parent->addChild(new Node(new ConstantOperation(std::stod(word))));
        }
        else if (isOperation(word)) {
            TreeBuildResult branchResult;
            branchResult = createBranch(words, parent->addChild(new Node(_operations[word])), _operations[word], result);
            if (!branchResult.isSuccess()) {
                return result;
            }
        }
        else if (isVariable(word)) {
            parent->addChild(new Node(new VariableOperation(word)));
        }
        else {
            result.addError("Invalid token '" + word + "' at '" + print() + "'.");
            return result;
        }
    }

    return result;
}

std::set<std::string> getAllVariablesUnderNode(Node *node, const std::set<std::string> &variableNames) {
    std::set<std::string> variables = variableNames;
    Operation *currentOperation = node->getOperation();

    if (currentOperation->getType() == OperationType::VARIABLE) {
        variables.insert(currentOperation->getName());
    }

    for (Node *child: node->getChildren()) {
        variables = getAllVariablesUnderNode(child, variables);
    }

    return variables;
}

std::set<std::string> Tree::getVariables() const {
    std::set<std::string> variableNames;

    return getAllVariablesUnderNode(_root, variableNames);
}

std::string Tree::print() const {
    std::string text;

    for (const std::string &token: _inputTokens) {
        text += token;

        if (token != _inputTokens.back()) {
            text += " ";
        }
    }

    return text;
}

TreeBuildResult Tree::join(const std::vector<std::string> &tokens) {
    Tree *tree = new Tree(tokens, _operations);
    TreeBuildResult buildResult = tree->buildTree();

    if (!buildResult.isSuccess()) {
        return buildResult;
    }
    
    _inputTokens.erase(_inputTokens.end() - 1);
    _inputTokens.insert(_inputTokens.end(), tree->_inputTokens.begin(), tree->_inputTokens.end());

    Node *rightLowerNode = _root;

    int childCount;
    while (!rightLowerNode->getChildren().empty()) {
        childCount = rightLowerNode->getChildren().size();
        rightLowerNode = rightLowerNode->getChildren()[childCount - 1];
    }
    
    rightLowerNode->getParent()->insertChild(childCount - 1, tree->_root->getChildren()[0]);

    return buildResult;
}

/*Tree Tree::operator+(const Tree &other) const {
    Tree *resultTree = new Tree(_inputTokens, _operations);
    resultTree->join(other._inputTokens);
    return *resultTree;
}

Tree Tree::operator=(const Tree &other) const {
    Tree resultTree = Tree(other._inputTokens, _operations);
    return resultTree;
}*/


