#include "TreeBuildResult.h"

void TreeBuildResult::addError(const std::string &error)
{
    _errors.push_back(error);
}

std::vector<std::string> TreeBuildResult::getErrors() const
{
    return _errors;
}

bool TreeBuildResult::isSuccess() const
{
    return _errors.empty();
}

std::vector<std::string> TreeBuildResult::getWarnings() const
{
    return _warnings;
}

void TreeBuildResult::addWarning(const std::string &warning)
{
    _warnings.push_back(warning);
}
