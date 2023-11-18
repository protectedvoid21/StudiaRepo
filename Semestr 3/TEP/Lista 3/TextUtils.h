#pragma once
#include <vector>
#include <string>

std::vector<std::string> splitByWhitespace(const std::string &text);

bool isNumber(const std::string &text);

bool isVariable(std::string text);