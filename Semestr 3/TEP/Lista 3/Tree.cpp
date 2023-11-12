#include <stdexcept>
#include "Tree.h"
#include "Operations.h"

Tree::Tree(const std::string& textInput, const std::map<std::string, Operation *>& operations) : _operations(operations) {
    _root = new Node(new InitOperation());
    parseToTree(textInput);
}

double Tree::evaluate(const std::map<std::string, double> &variables) {
    return _root->evaluate(variables);
}

std::vector<std::string> splitByWhitespace(std::string text) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char c: text) {
        if (c == ' ') {
            if (currentToken.length() > 0) {
                tokens.push_back(currentToken);
                currentToken = "";
            }
        }
        else {
            currentToken += c;
        }
    }

    if (currentToken.length() > 0) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

bool isNumber(std::string text) {
    for (char c: text) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }

    return true;
}

bool isVariable(std::string text) {
    if(text.length() == 0) {
        return false;
    }
    if(!isalpha(text[0])) {
        return false;
    }
    
    for(char c : text) {
        if(!isalnum(c)) {
            return false;
        }
    }

    return true;
}

bool Tree::isOperation(const std::string &text) {
    return _operations[text] != NULL;
}

void Tree::createBranch(std::vector<std::string> words, Node *parent, Operation *operation) {
    if(words.size() < operation->getParameterCount()) {
        throw std::invalid_argument("Not enough parameters for operation");
    }
    
    for(int i = 0; i < operation->getParameterCount(); i++) {
        std::string word = words.front();
        words.erase(words.begin());
        
        if (isNumber(word)) {
            parent->addChild(new Node(new ConstantOperation(10)));
        }
        else if (isOperation(word)) {
            createBranch(words, parent->addChild(new Node(_operations[word])), _operations[word]);
        }
        else if(isVariable(word)) {
            parent->addChild(new Node(new VariableOperation(word)));
        }
        else {
            throw std::invalid_argument("Invalid variable name");
        }
    }
}

void Tree::parseToTree(std::string textInput) {
    std::vector<std::string> words = splitByWhitespace(textInput);

    createBranch(words, _root, new InitOperation());
}
