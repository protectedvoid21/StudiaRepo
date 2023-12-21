#include <vector>
#include <string>

class TreeBuildResult
{
    std::vector<std::string> _errors;
    std::vector<std::string> _warnings;
public:
    void addError(const std::string &error);
    void addWarning(const std::string &warning);
    std::vector<std::string> getErrors() const;
    std::vector<std::string> getWarnings() const;
    bool isSuccess() const;

};