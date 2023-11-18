#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <map>
#include "Operations.h"
#include "Tree.h"
#include "TextUtils.h"

std::map<std::string, Operation *> generateOperationsMap() {
    std::map<std::string, Operation *> operations;
    operations["+"] = new AddOperation();
    operations["-"] = new SubtractOperation();
    operations["*"] = new MultiplyOperation();
    operations["/"] = new DivideOperation();
    operations["sin"] = new SinOperation();
    operations["cos"] = new CosOperation();

    return operations;
}

void testFunction(const std::string &input, const std::map<std::string, Operation *> &operations,
                  const std::map<std::string, double> &variables, double expected) {

    std::vector<std::string> tokens = splitByWhitespace(input);
    Tree tree(tokens, operations);
    
    tree.buildTree();

    CHECK(tree.evaluate(variables) == expected);
}


TEST_CASE("TestCorrectInputWithoutVariables") {
    auto operations = generateOperationsMap();
    
    testFunction("+ + 3 4 5", operations, std::map<std::string, double>(), 12);
    testFunction("+ * 5 7 - 10 3", operations, std::map<std::string, double>(), 42);
    testFunction("+ * 5 4 * + 5 2 8", operations, std::map<std::string, double>(), 76);
}

TEST_CASE("EmptyInput") {
    auto operations = generateOperationsMap();
    
    testFunction("", operations, std::map<std::string, double>(), 0);
}

TEST_CASE("TestCorrectInputWithVariables") {
    auto operations = generateOperationsMap();
    std::map<std::string, double> variables;
    variables["x"] = 3;
    variables["a"] = 5;
    variables["b"] = 2;
    
    testFunction("+ * 5 x * + a b 8", operations, variables, 71);
}

std::set<std::string> getVariables(const std::string &input) {
    auto operations = generateOperationsMap();
    auto tokens = splitByWhitespace(input);
    Tree tree(tokens, operations);
    
    tree.buildTree();
    
    return tree.getVariables();
}

TEST_CASE("TestGetVariables") {
    auto operations = generateOperationsMap();
    std::map<std::string, double> variables;
    variables["x"] = 3;
    variables["a"] = 5;
    variables["b"] = 2;
    
    std::set<std::string> expected;
    expected.insert("x");
    expected.insert("a");
    expected.insert("b");
    
    CHECK(getVariables("+ * 5 x * + a b 8") == expected);
}

TEST_CASE("TestGetVariablesWithoutAny") {
    auto operations = generateOperationsMap();
    std::map<std::string, double> variables;

    std::set<std::string> expected;

    CHECK(getVariables("+ * 5 9 * + 1 5 8") == expected);
}


std::string getPrint(const std::string &input) {
    auto operations = generateOperationsMap();

    auto tokens = splitByWhitespace(input);
    Tree tree(tokens, operations);

    tree.buildTree();
    
    return tree.print();
}

TEST_CASE("TestPrint") {
    CHECK(getPrint("+ * 5 x + a b 8") == "+ * 5 x + a b");
    CHECK(getPrint("+ 3 5") == "+ 3 5");
}