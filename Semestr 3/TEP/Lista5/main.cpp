#include <iostream>
#include "MySmartPointer.h"

void foo(MySmartPointer<int> ptr)
{
    std::cout << *ptr << std::endl;
}

int main()
{
    MySmartPointer<int> ptr(new int(5));
    foo(ptr);
    
    std::cout << *ptr << std::endl;
}
