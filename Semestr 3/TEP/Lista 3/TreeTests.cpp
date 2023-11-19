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

Tree getTree(const std::string &input) {
    auto operations = generateOperationsMap();
    auto tokens = splitByWhitespace(input);
    Tree tree(tokens, operations);

    tree.buildTree();

    return tree;
}

double getEvaluation(const std::string &input, const std::map<std::string, double> &variables) {
    auto tree = getTree(input);

    return tree.evaluate(variables);
}

std::set<std::string> getVariables(const std::string &input) {
    auto tree = getTree(input);

    return tree.getVariables();
}

std::string getPrint(const std::string &input) {
    auto tree = getTree(input);

    return tree.print();
}

std::string getJoin(const std::string &input1, const std::string &input2) {
    auto operations = generateOperationsMap();

    auto tokens1 = splitByWhitespace(input1);
    auto tokens2 = splitByWhitespace(input2);

    Tree tree1(tokens1, operations);
    Tree tree2(tokens2, operations);

    tree1.buildTree();
    tree2.buildTree();

    Tree tree3 = tree1 + tree2;

    return tree3.print();
}


TEST_CASE("TestCorrectInputWithoutVariables") {
    CHECK(getEvaluation("+ + 3 4 5", std::map<std::string, double>()) == 12);
    CHECK(getEvaluation("+ * 5 7 - 10 3", std::map<std::string, double>()) == 42);
    CHECK(getEvaluation("+ * 5 4 * + 5 2 8", std::map<std::string, double>()) == 76);
}

TEST_CASE("EmptyInput") {
    CHECK(getEvaluation("", std::map<std::string, double>()) == 1);
}

TEST_CASE("TestCorrectInputWithVariables") {
    std::map<std::string, double> variables = {{"x", 3}, {"a", 5}, {"b", 2}};

    CHECK(getEvaluation("+ * 5 x * + a b 8", variables) == 71);
}

TEST_CASE("TestGetVariables") {
    CHECK(getVariables("+ * 5 x * + a b 8") == std::set<std::string>{"x", "a", "b"});
    CHECK(getVariables("+ * 5 1 * + 5 10 8") == std::set<std::string>{});
    CHECK(getVariables("+ * 5 9 * + 1 5 8") == std::set<std::string>{});
    CHECK(getVariables("b") == std::set<std::string>{"b"});
    CHECK(getVariables("") == std::set<std::string>{});
    CHECK(getVariables("5") == std::set<std::string>{});
}

TEST_CASE("TestPrint") {
    CHECK(getPrint("+ * 5 x + a b 8") == "+ * 5 x + a b");
    CHECK(getPrint("+ 3 5") == "+ 3 5");
}

TEST_CASE("TestJoinOperator") {
    CHECK(getJoin("+ 3 5", "* 2 4") == "+ 3 * 2 4");
    CHECK(getJoin("+ 3", "- 10 20") == "+ 3 - 10 20");
    CHECK(getJoin("", "+ 10 20") == "+ 10 20");
}

TEST_CASE("RepairInvalidInputByAddingParameters") {
    CHECK(getPrint("+ 3") == "+ 3 1");
    CHECK(getPrint("+ +") == "+ + 1 1 1");
    CHECK(getPrint("+ + 3") == "+ + 3 1 1");
    CHECK(getPrint("+ + +") == "+ + + 1 1 1 1");
    CHECK(getPrint("+") == "+ 1 1");
}