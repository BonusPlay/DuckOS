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

    ADD_CUSTOM_TARGET(test
        COMMAND ${CMAKE_SOURCE_DIR}/build/tests/tests
        USES_TERMINAL
    )
endif()

ADD_CUSTOM_TARGET(image
    COMMAND sudo ${CMAKE_SOURCE_DIR}/scripts/build-image.sh
    BYPRODUCTS ${CMAKE_BINARY_DIR}/duckOS.img
    USES_TERMINAL
)

ADD_CUSTOM_TARGET(qemu-image
    COMMAND ${CMAKE_SOURCE_DIR}/scripts/run-qemu-image.sh
    USES_TERMINAL
)
