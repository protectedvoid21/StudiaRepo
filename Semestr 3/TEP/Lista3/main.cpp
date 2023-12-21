#include <iostream>
#include "TreeManager.h"
#include "Tree.h"
#include "Operations.h"

void testOperators()
{
    std::map<std::string, Operation *> operations;
    operations["+"] = new AddOperation();
    operations["-"] = new SubtractOperation();
    operations["*"] = new MultiplyOperation();
    operations["/"] = new DivideOperation();
    operations["sin"] = new SinOperation();
    operations["cos"] = new CosOperation();

    std::vector<std::string> tree1Input = splitByWhitespace("+ + 3 5 * 2 4");
    std::vector<std::string> tree2Input = splitByWhitespace("* - 10 1 + 5 1");

    Tree tree1(tree1Input, operations);
    Tree tree2(tree2Input, operations);

    tree1.buildTree();
    tree2.buildTree();

    std::cout << "Tree built." << std::endl;

    Tree tree3 = tree1 + tree2;
    std::cout << tree3.print() << std::endl;
    std::cout << tree3.evaluate(std::map<std::string, double>()) << std::endl;
}

void runTreeManager()
{
    std::map<std::string, Operation *> operations;
    operations["+"] = new AddOperation();
    operations["-"] = new SubtractOperation();
    operations["*"] = new MultiplyOperation();
    operations["/"] = new DivideOperation();
    operations["sin"] = new SinOperation();
    operations["cos"] = new CosOperation();

    std::string input;

    TreeManager treeManager(operations);

    while (input != "exit")
    {
        std::cout << "Enter command: ";
        std::getline(std::cin, input);
        treeManager.getInput(input);
    }
}

int main()
{
    //testOperators();
    runTreeManager();
}