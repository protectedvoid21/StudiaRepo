#include "TreeManager.h"


TreeManager::TreeManager(const std::map<std::string, Operation *> &operations) {
    _tree = nullptr;
    _operations = operations;
}

void TreeManager::getInput(const std::string &textInput) {
    std::vector<std::string> tokens = splitByWhitespace(textInput);

    if (tokens.empty()) {
        std::cout << "No input given." << std::endl;
        return;
    }

    std::string commandName = tokens[0];
    tokens.erase(tokens.begin());

    if (commandName == "enter") {
        createTree(tokens);
    }
    else if (_tree == nullptr) {
        std::cout << "Tree has not been created. Use 'enter' command to create a tree" << std::endl;
        return;
    }
    else if (commandName == "print") {
        print();
    }
    else if (commandName == "vars") {
        getVariables();
    }
    else if (commandName == "join") {
        join(tokens);
    }
    else if (commandName == "comp") {
        compute(tokens);
    }
    else {
        std::cout << "Invalid command." << std::endl;
    }
}

void TreeManager::createTree(std::vector<std::string> &tokens) {
    if (tokens.empty()) {
        std::cout << "No tree name given." << std::endl;
        return;
    }

    _tree = new Tree(tokens, _operations);

    TreeBuildResult buildResult = _tree->buildTree();

    for(const std::string &error: buildResult.getErrors()) {
        std::cout << "[ERROR]: " << error << std::endl;
    }
    for(const std::string &warning: buildResult.getWarnings()) {
        std::cout << "[WARNING]: " << warning << std::endl;
    }
    
    if (!buildResult.isSuccess()) {
        return;
    }
    std::cout << "Tree has been created successfully." << std::endl;
}

void TreeManager::compute(std::vector<std::string> &tokens) {
    std::set<std::string> variables = _tree->getVariables();

    if (tokens.size() < variables.size()) {
        std::cout << "You have not passed value for every variable." << std::endl;
        return;
    }
    if (tokens.size() > variables.size()) {
        std::cout << "You have passed too many values." << std::endl;
        return;
    }

    std::map<std::string, double> variablesMap;
    int tokenIndex = 0;
    for (const std::string &variable: variables) {
        variablesMap[variable] = std::stod(tokens[tokenIndex]);
        tokenIndex++;
    }

    std::cout << _tree->evaluate(variablesMap) << std::endl;
}

void TreeManager::join(std::vector<std::string> &tokens) {
    if (tokens.empty()) {
        std::cout << "No parameters were given." << std::endl;
        return;
    }

    TreeBuildResult joinResult = _tree->join(tokens);
    
    for(const std::string &error: joinResult.getErrors()) {
        std::cout << "[ERROR]: " << error << std::endl;
    }
    for(const std::string &warning: joinResult.getWarnings()) {
        std::cout << "[WARNING]: " << warning << std::endl;
    }

    if (!joinResult.isSuccess()) {
        return;
    }
    std::cout << "Tree has been joined successfully." << std::endl;
}

void TreeManager::print() const {
    std::cout << _tree->print() << std::endl;
}

void TreeManager::getVariables() const {
    std::cout << "Variables: ";
    std::set<std::string> variables = _tree->getVariables();

    bool firstElement = true;

    for (const std::string &variable: variables) {
        std::cout << (firstElement ? "" : " ") << variable;
        firstElement = false;
    }

    std::cout << std::endl;
}