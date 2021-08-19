cmake_minimum_required(VERSION 3.13)
project(DuckOS
    LANGUAGES CXX ASM
    VERSION 0.1.0
    DESCRIPTION "DuckOS is custom OS written in C++ for fun"
)

# https://stackoverflow.com/a/9328525/13212650
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

option(BUILD_KERNEL "Builds kernel" ON)
option(BUILD_TESTS "Builds unit tests" OFF)

add_subdirectory(dstd)

if(${BUILD_KERNEL})
    add_subdirectory(kernel)
endif()

if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()
