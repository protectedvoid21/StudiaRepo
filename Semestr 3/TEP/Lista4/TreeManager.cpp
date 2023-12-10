#include <iomanip>

template <typename T>
TreeManager<T>::TreeManager(const std::map<std::string, Operation<T> *> &operations)
{
    _tree = nullptr;
    _operations = operations;
}

template <typename T>
std::vector<std::string> tokenize(const std::string &text)
{
    return splitByWhitespace(text);
}

template <>
std::vector<std::string> tokenize<std::string>(const std::string &text)
{
    return splitBySymbol(text, '"');
}

template <typename T>
void TreeManager<T>::getInput(const std::string &textInput)
{
    std::vector<std::string> tokens = tokenize<T>(textInput);

    if (tokens.empty())
    {
        std::cout << "No input given." << std::endl;
        return;
    }

    std::string commandName = tokens[0];
    tokens.erase(tokens.begin());

    if (commandName == ENTER_COMMAND)
    {
        createTree(tokens);
    }
    else if (_tree == nullptr)
    {
        std::cout << "Tree has not been created. Use 'enter' command to create a tree" << std::endl;
        return;
    }
    else if (commandName == PRINT_COMMAND)
    {
        print();
    }
    else if (commandName == VARS_COMMAND)
    {
        getVariables();
    }
    else if (commandName == JOIN_COMMAND)
    {
        join(tokens);
    }
    else if (commandName == COMP_COMMAND)
    {
        compute(tokens);
    }
    else
    {
        std::cout << "Invalid command." << std::endl;
    }
}

template <typename T>
void TreeManager<T>::createTree(std::vector<std::string> &tokens)
{
    if (tokens.empty())
    {
        std::cout << "No tree name given." << std::endl;
        return;
    }

    _tree = new Tree(tokens, _operations);
    TreeBuildResult buildResult = _tree->buildTree();

    for (const std::string &error : buildResult.getErrors())
    {
        std::cout << "[ERROR]: " << error << std::endl;
    }
    for (const std::string &warning : buildResult.getWarnings())
    {
        std::cout << "[WARNING]: " << warning << std::endl;
    }

    if (!buildResult.isSuccess())
    {
        return;
    }
    std::cout << "Tree has been created successfully." << std::endl;
}

template <typename T>
T TreeManager<T>::extractValue(const std::string &text) const
{
    return static_cast<T>(text);
}

template <>
std::string TreeManager<std::string>::extractValue(const std::string &text) const
{
    if (text[0] == '"') {
        return text.substr(1, text.size() - 2);
    }
    return text;
}

template <>
int TreeManager<int>::extractValue(const std::string &text) const
{
    return std::stoi(text);
}

template <>
double TreeManager<double>::extractValue(const std::string &text) const
{
    return std::stod(text);
}

template <typename T>
void TreeManager<T>::compute(std::vector<std::string> &tokens)
{
    std::set<std::string> variables = _tree->getVariables();

    if (tokens.size() < variables.size())
    {
        std::cout << "You have not passed value for every variable." << std::endl;
        return;
    }
    if (tokens.size() > variables.size())
    {
        std::cout << "You have passed too many values." << std::endl;
        return;
    }

    std::map<std::string, T> variablesMap;
    int tokenIndex = 0;
    for (const std::string &variable : variables)
    {
        variablesMap[variable] = extractValue(tokens[tokenIndex]);
        tokenIndex++;
    }

    std::cout << _tree->evaluate(variablesMap) << std::endl;
}

template <typename T>
void TreeManager<T>::join(std::vector<std::string> &tokens)
{
    if (tokens.empty())
    {
        std::cout << "No parameters were given." << std::endl;
        return;
    }

    TreeBuildResult joinResult = _tree->join(tokens);

    for (const std::string &error : joinResult.getErrors())
    {
        std::cout << "[ERROR]: " << error << std::endl;
    }
    for (const std::string &warning : joinResult.getWarnings())
    {
        std::cout << "[WARNING]: " << warning << std::endl;
    }

    if (!joinResult.isSuccess())
    {
        return;
    }
    std::cout << "Tree has been joined successfully." << std::endl;
}

template <typename T>
void TreeManager<T>::print() const
{
    std::cout << _tree->print() << std::endl;
}

template <typename T>
void TreeManager<T>::getVariables() const
{
    std::cout << "Variables: ";
    std::set<std::string> variables = _tree->getVariables();

    bool firstElement = true;

    for (const std::string &variable : variables)
    {
        std::cout << (firstElement ? "" : " ") << variable;
        firstElement = false;
    }

    std::cout << std::endl;
}