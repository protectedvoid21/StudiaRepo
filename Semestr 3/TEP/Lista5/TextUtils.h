#pragma once

#include <vector>
#include <string>

std::vector<std::string> splitByWhitespace(const std::string &text);

std::vector<std::string> splitBySymbol(const std::string &text, char symbol);

bool isNumber(const std::string &text);

bool isVariable(std::string text);