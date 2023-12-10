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

std::vector<std::string> splitBySymbol(const std::string &text, char symbol)
{
    std::vector<std::string> tokens;
    bool currentlyInString = false;
    std::string currentToken = "";

    for (int i = 0; i < text.size(); ++i)
    {
        if (text[i] == symbol)
        {
            currentlyInString = !currentlyInString;
        }
        if (currentlyInString)
        {
            currentToken += text[i];
        }
        else if (text[i] != ' ')
        {
            currentToken += text[i];
        }
        else if (!currentToken.empty())
        {
            tokens.push_back(currentToken);
            currentToken = "";
        }
    }

    if (!currentToken.empty())
    {
        tokens.push_back(currentToken);
    }

    return tokens;
}
