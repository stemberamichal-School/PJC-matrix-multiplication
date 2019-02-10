cmake_minimum_required(VERSION 3.5)
project(matrix-multiplication LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COMMON_SOURCES
        Matrix.cpp
        Matrix.hpp
        MatrixBase.cpp
        MatrixBase.hpp
        MatrixRow.cpp
        MatrixRow.hpp
        MatrixView.cpp
        MatrixView.hpp
        MergeOperation.cpp
        MergeOperation.hpp
        MultiplicationContext.cpp
        MultiplicationContext.hpp
        MultiplyOperation.cpp
        MultiplyOperation.hpp
        Operation.cpp
        Operation.hpp
        OperationQueue.cpp
        OperationQueue.hpp
        OptionControl.cpp
        OptionControl.hpp
        ReadOperation.cpp
        ReadOperation.hpp
        Shared.hpp
        SplitOperation.cpp
        SplitOperation.hpp
        TestOperation.cpp
        TestOperation.hpp
        WriteOperation.cpp
        WriteOperation.hpp
        # Případné další soubory přidávejte sem
        # Funkce main musí být v souboru main.cpp, který se linkuje jen pro target matrix-multiplication
        )

# Vlastní aplikace.
add_executable(matrix-multiplication ${COMMON_SOURCES} main.cpp)


# Chceme být schopní includovat knihovnu mapbox pomocí <>
include_directories(.)

if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    add_compile_options(-Wall -Wextra -Wunreachable-code -Wpedantic -pthread)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    add_compile_options(/W4)
endif()


if (${CMAKE_VERSION} VERSION_GREATER 3.5)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests-direct)
endif()

if ( CMAKE_BUILD_TYPE MATCHES "Release|RelWithDebInfo" )
    message(STATUS "Registering long tests to CTest")
    add_test(NAME complex-tests-direct COMMAND tests-runner-direct [.long])
    add_test(NAME complex-tests-subprocess COMMAND tests-runner-subprocess [.long])
    set_tests_properties(complex-tests-direct PROPERTIES ENVIRONMENT TEST_CMD="${TEST_CMD}")
    set_tests_properties(complex-tests-subprocess PROPERTIES ENVIRONMENT TEST_CMD="${TEST_CMD}")
endif()
