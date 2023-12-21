#include "TextUtils.h"

std::vector<std::string> splitByWhitespace(const std::string &text)
{
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char c : text)
    {
        if (c == ' ')
        {
            if (currentToken.length() > 0)
            {
                tokens.push_back(currentToken);
                currentToken = "";
            }
        }
        else
        {
            currentToken += c;
        }
    }

    if (currentToken.length() > 0)
    {
        tokens.push_back(currentToken);
    }

    return tokens;
}

bool isNumber(const std::string &text)
{
    for (char c : text)
    {
        if (!isdigit(c) && c != '.')
        {
            return false;
        }
    }

    return true;
}

bool isVariable(std::string text)
{
    if (text.length() == 0)
    {
        return false;
    }
    if (!isalpha(text[0]))
    {
        return false;
    }

    for (char c : text)
    {
        if (!isalnum(c))
        {
            return false;
        }
    }

    return true;
}
