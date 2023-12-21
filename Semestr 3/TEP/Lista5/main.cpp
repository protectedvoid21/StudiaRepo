#include <iostream>
#include "Tree.h"
#include "Operation.h"
#include "Operations.h"
#include "TextUtils.h"
#include "MySmartPointer.h"

void foo()
{
    MySmartPointer<int> arr = MySmartPointer<int>(new int[10]);

    for (int i = 0; i < 10; i++)
    {
        arr.operator->()[i]= i;
    }

    for (int i = 0; i < 10; ++i)
    {
        std::cout << arr.operator->()[i] << " " << std::endl;
    }
}

int main()
{
    std::vector<std::string> firstTreeTokens = splitByWhitespace("+ 120 * 2 - / 50 2 1");
    std::vector<std::string> secondTreeTokens = splitByWhitespace("+ 5 3");
    
    std::map<std::string, Operation<int> *> operationMap = std::map<std::string, Operation<int> *>();
    operationMap["+"] = new AddOperation<int>();
    operationMap["-"] = new SubtractOperation<int>();
    operationMap["*"] = new MultiplyOperation<int>();
    operationMap["/"] = new DivideOperation<int>();
    
    Tree<int> firstTree = Tree<int>(firstTreeTokens, operationMap);
    Tree<int> secondTree = Tree<int>(secondTreeTokens, operationMap);
    
    std::cout << "First tree: " << firstTree.print() << std::endl;
    std::cout << "Second tree: " << secondTree.print() << std::endl;
    
    secondTree = std::move(firstTree);
    
    std::cout << "First tree: " << firstTree.print() << std::endl;
    std::cout << "Second tree: " << secondTree.print() << std::endl;
    //foo();
    
    MySmartPointer<int> intPtr = MySmartPointer<int>(new int(5));
    MySmartPointer<int> otherPtr = intPtr.duplicate();
    
    *otherPtr = 20;
    
    std::cout << *intPtr << std::endl;
    std::cout << *otherPtr << std::endl;
}