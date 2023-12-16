#include "Tree.h"
#include "TextUtils.h"

template <typename T>
Tree<T>::Tree(const std::vector<std::string> &tokens, const std::map<std::string, Operation<T> *> &operations) : _operations(operations)
        {
                _inputTokens = tokens;
        _root = new Node(new InitOperation<T>());
        }

template <typename T>
Tree<T>::~Tree()
{
    delete _root;
}

template <typename T>
TreeBuildResult Tree<T>::buildTree()
{
    std::vector<std::string> tokens;
    tokens.reserve(_inputTokens.size());

    for (const std::string &token : _inputTokens)
    {
        tokens.push_back(token);
    }
    TreeBuildResult result;
    result = createBranch(tokens, _root, new InitOperation<T>(), result);

    if (!tokens.empty())
    {
        std::string warningText = "Too many parameters for some operations. These parameters will be ignored:";

        for (const std::string &word : tokens)
        {
            warningText += " " + word;
            _inputTokens.erase(tokens.begin());
        }

        result.addWarning(warningText);
    }

    return result;
}

template <typename T>
T Tree<T>::evaluate(const std::map<std::string, T> &variables)
{
    return _root->evaluate(variables);
}

template <typename T>
bool Tree<T>::isOperation(const std::string &text)
{
    return _operations[text] != nullptr;
}

template <typename T>
T stringToValue(const std::string &text)
{
    return static_cast<T>(text);
}

template <>
int stringToValue<int>(const std::string &text)
{
    return std::stoi(text);
}

template <>
double stringToValue<double>(const std::string &text)
{
    return std::stod(text);
}

template <>
bool stringToValue<bool>(const std::string &text)
{
    return text != "0";
}

template <typename T>
TreeBuildResult Tree<T>::createBranch(std::vector<std::string> &words, Node<T> *parent, Operation<T> *operation, TreeBuildResult &result)
{
    for (int i = 0; i < operation->getParameterCount(); i++)
    {
        if (words.empty())
        {
            result.addWarning("Not enough parameters for operation at '" + print() + "'. Adding \"Sample text\" as parameter.");

            words.emplace_back("Sample text");
            _inputTokens.emplace_back("Sample text");
        }
        std::string word = words.front();
        words.erase(words.begin());

        if (isNumber(word))
        {
            parent->addChild(new Node(new ConstantOperation<T>(stringToValue<T>(word))));
        }
        else if (isOperation(word))
        {
            TreeBuildResult branchResult;
            branchResult = createBranch(words, parent->addChild(new Node(_operations[word])), _operations[word], result);
            if (!branchResult.isSuccess())
            {
                return branchResult;
            }
        }
        else if (isVariable(word))
        {
            parent->addChild(new Node(new VariableOperation<T>(word)));
        }
        else
        {
            result.addWarning("Invalid token '" + word + "' at '" + print() + "'. Replacing it with \"Sample text\".");
            parent->addChild(new Node(new ConstantOperation<T>(stringToValue<T>("Sample text"))));
        }
    }

    return result;
}

template <typename T>
std::set<std::string> getAllVariablesUnderNode(Node<T> *node, const std::set<std::string> &variableNames)
{
    std::set<std::string> variables = variableNames;
    Operation<T> *currentOperation = node->getOperation();

    if (currentOperation->getType() == OperationType::VARIABLE)
    {
        variables.insert(currentOperation->getName());
    }

    for (Node<T> *child : node->getChildren())
    {
        variables = getAllVariablesUnderNode(child, variables);
    }

    return variables;
}

template <typename T>
std::set<std::string> Tree<T>::getVariables() const
{
    std::set<std::string> variableNames;

    return getAllVariablesUnderNode(_root, variableNames);
}

template <typename T>
std::string Tree<T>::print() const
{
    std::string text;

    if (!_inputTokens.empty())
    {
        text += _inputTokens[0];
    }
    for (int i = 1; i < _inputTokens.size(); i++)
    {
        text += " " + _inputTokens[i];
    }

    return text;
}

template <typename T>
TreeBuildResult Tree<T>::join(const std::vector<std::string> &tokens)
{
    Tree *tree = new Tree(tokens, _operations);
    TreeBuildResult buildResult = tree->buildTree();

    if (!buildResult.isSuccess())
    {
        return buildResult;
    }

    _inputTokens.erase(_inputTokens.end() - 1);
    _inputTokens.insert(_inputTokens.end(), tree->_inputTokens.begin(), tree->_inputTokens.end());

    Node<T> *rightLowerNode = _root;

    int childCount;
    while (!rightLowerNode->getChildren().empty())
    {
        childCount = rightLowerNode->getChildren().size();
        rightLowerNode = rightLowerNode->getChildren()[childCount - 1];
    }

    rightLowerNode->getParent()->insertChild(childCount - 1, tree->_root->getChildren()[0]);

    return buildResult;
}

template <typename T>
Tree<T> Tree<T>::operator+(const Tree<T> &other)
{
    Tree resultTree = Tree(_inputTokens, _operations);
    resultTree.join(other._inputTokens);
    resultTree.buildTree();
    return resultTree;
}

template <typename T>
Tree<T> Tree<T>::operator=(const Tree<T> &other)
{
    if (this == &other)
    {
        return *this;
    }

    _inputTokens = other._inputTokens;
    _root = other._root;
    _operations = other._operations;
    return *this;
}

//Specializations for std::string

bool isStringConstant(const std::string &text)
{
    char firstLetter = text[0];
    char lastLetter = text[text.size() - 1];
    return firstLetter == '"' && lastLetter == '"';
}

template <>
TreeBuildResult Tree<std::string>::createBranch(std::vector<std::string> &words, Node<std::string> *parent, Operation<std::string> *operation, TreeBuildResult &result)
{
    for (int i = 0; i < operation->getParameterCount(); i++)
    {
        if (words.empty())
        {
            result.addWarning("Not enough parameters for operation at '" + print() + "'. Adding \"1\" as parameter.");

            words.emplace_back("\"1\"");
            _inputTokens.emplace_back("\"1\"");
        }
        std::string word = words.front();
        words.erase(words.begin());

        if (isStringConstant(word))
        {
            std::string wordWithoutQuotes = word.substr(1, word.size() - 2);
            parent->addChild(new Node(new ConstantOperation<std::string>(wordWithoutQuotes)));
        }
        else if (isOperation(word))
        {
            TreeBuildResult branchResult;
            branchResult = createBranch(words, parent->addChild(new Node(_operations[word])), _operations[word], result);
            if (!branchResult.isSuccess())
            {
                return branchResult;
            }
        }
        else if (isVariable(word))
        {
            parent->addChild(new Node(new VariableOperation<std::string>(word)));
        }
        else
        {
            result.addError("Invalid token '" + word + "' at '" + print() + "'.");
            return result;
        }
    }

    return result;
}

//specializations for bool

template <>
TreeBuildResult Tree<bool>::createBranch(std::vector<std::string> &words, Node<bool> *parent, Operation<bool> *operation, TreeBuildResult &result)
{
    if (parent != _root && operation->getParameterCount() == 1)
    {
        result.addError("Invalid operation at '" + print() + "'.");
        result.addError("Create new tree otherwise you may get unexpected results.");
        _root = new Node(new InitOperation<bool>());
        return result;
    }
    
    for (int i = 0; i < operation->getParameterCount(); i++)
    {
        if (words.empty())
        {
            result.addWarning("Not enough parameters for operation at '" + print() + "'. Adding false as parameter.");

            words.emplace_back("0");
            _inputTokens.emplace_back("0");
        }
        std::string word = words.front();
        words.erase(words.begin());

        if (isNumber(word))
        {
            parent->addChild(new Node(new ConstantOperation<bool>(stringToValue<bool>(word))));
        }
        else if (isOperation(word))
        {
            TreeBuildResult branchResult;
            branchResult = createBranch(words, parent->addChild(new Node(_operations[word])), _operations[word], result);
            if (!branchResult.isSuccess())
            {
                return branchResult;
            }
        }
        else if (isVariable(word))
        {
            parent->addChild(new Node(new VariableOperation<bool>(word)));
        }
        else
        {
            result.addWarning("Invalid token '" + word + "' at '" + print() + "'. Replacing it with false.");
            parent->addChild(new Node(new ConstantOperation<bool>(false)));
        }
    }

    return result;
}