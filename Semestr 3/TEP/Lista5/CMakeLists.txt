cmake_minimum_required(VERSION 3.26)
project(Lista5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lista5 main.cpp
        MySmartPointer.h
        Operation.h
        Operations.h
        TextUtils.h
        TreeManager.h
        TextUtils.cpp
        TreeBuildResult.cpp
        TreeBuildResult.h
        RefCounter.h
)
        
