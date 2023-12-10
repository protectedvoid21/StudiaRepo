cmake_minimum_required(VERSION 3.26)
project(TEP)

set(CMAKE_CXX_STANDARD 17)

# Dodaj pliki źródłowe do biblioteki
add_library(MyLib
        Operation.h
        Operations.h
        TextUtils.h
        TreeManager.h
        TextUtils.cpp
        TreeBuildResult.cpp
        TreeBuildResult.h
)

# Dodaj pliki źródłowe do celu aplikacji
add_executable(Main
        main.cpp
)

# Dodaj pliki źródłowe do celu testów
add_executable(Tests
        TreeTests.cpp
)

# Dodaj Doctest jako bibliotekę do celu testów
target_compile_definitions(Tests PRIVATE DOCTEST_CONFIG_IMPLEMENT)
target_include_directories(Tests PRIVATE path/to/doctest)

# Linkuj aplikację i testy do biblioteki
target_link_libraries(Main PRIVATE MyLib)
target_link_libraries(Tests PRIVATE MyLib)