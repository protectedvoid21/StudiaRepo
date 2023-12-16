#include "RefCounter.h"

template<typename T>
class MySmartPointer
{
private:
    RefCounter *refCounter;
    T *pointer;
    
public:
    MySmartPointer(T *pcPointer)
    {
        pointer = pcPointer;
        refCounter = new RefCounter();
        refCounter->add();
    }

    MySmartPointer(const MySmartPointer &pcOther)
    {
        pointer = pcOther.pointer;
        refCounter = pcOther.refCounter;
        refCounter->add();
    }

    ~MySmartPointer()
    {
        if (refCounter->dec() == 0)
        {
            delete pointer;
            delete refCounter;
        }
    }
    
    T operator=(const MySmartPointer &pcOther)
    {
        if(this == &pcOther) return *this;
        
        if (refCounter->dec() == 0)
        {
            delete pointer;
            delete refCounter;
        }

        pointer = pcOther.pointer;
        refCounter = pcOther.refCounter;
        refCounter->add();
        
        return *this;
    }

    T &operator*()
    {
        return *pointer;
    }

    T *operator->()
    {
        return pointer;
    }
};