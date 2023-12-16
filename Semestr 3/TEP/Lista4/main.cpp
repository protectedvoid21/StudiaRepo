#include <iostream>
#include "TreeManager.h"
#include "Tree.h"
#include "Operations.h"

template <typename T>
void testOperators()
{
    std::map<std::string, Operation<T> *> operations;
    operations["+"] = new AddOperation<T>();
    operations["-"] = new SubtractOperation<T>();
    operations["*"] = new MultiplyOperation<T>();
    operations["/"] = new DivideOperation<T>();
    operations["sin"] = new SinOperation<T>();
    operations["cos"] = new CosOperation<T>();

    std::vector<std::string> tree1Input = splitByWhitespace("+ + 3 5 * 2 4");
    std::vector<std::string> tree2Input = splitByWhitespace("* - 10 1 / 12 5");

    Tree<T> tree1(tree1Input, operations);
    Tree<T> tree2(tree2Input, operations);

    tree1.buildTree();
    tree2.buildTree();

    std::cout << "Tree built." << std::endl;

    Tree<T> tree3 = tree1 + tree2;
    std::cout << tree3.print() << std::endl;
    std::cout << tree3.evaluate(std::map<std::string, T>()) << std::endl;
}

template <typename T>
void runTreeManager()
{
    std::map<std::string, Operation<T> *> operations;
    operations["+"] = new AddOperation<T>();
    operations["-"] = new SubtractOperation<T>();
    operations["*"] = new MultiplyOperation<T>();
    operations["/"] = new DivideOperation<T>();
    operations["sin"] = new SinOperation<T>();
    operations["cos"] = new CosOperation<T>();

    std::string input;

    TreeManager<T> treeManager(operations);

    while (input != "exit")
    {
        std::cout << "Enter command: ";
        std::getline(std::cin, input);
        treeManager.getInput(input);
    }
}

void testStringTree() 
{
    std::map<std::string, Operation<std::string> *> operations;
    operations["+"] = new AddOperation<std::string>();
    operations["-"] = new SubtractOperation<std::string>();
    operations["*"] = new MultiplyOperation<std::string>();
    operations["/"] = new DivideOperation<std::string>();

    std::vector<std::string> tree1Input = splitByWhitespace("+ ala makota");
    std::vector<std::string> tree2Input = splitByWhitespace("+ kot maale");

    Tree<std::string> tree1(tree1Input, operations);
    Tree<std::string> tree2(tree2Input, operations);

    tree1.buildTree();
    tree2.buildTree();

    std::cout << "Tree built." << std::endl;

    Tree<std::string> tree3 = tree1 + tree2;
    std::cout << tree3.print() << std::endl;
}

int main()
{
    //testStringTree();
    //testOperators<double>();
    //runTreeManager<int>();
    //runTreeManager<double>();
    //runTreeManager<std::string>();
    runTreeManager<bool>();
}