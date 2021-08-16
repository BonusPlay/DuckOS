cmake_minimum_required(VERSION 3.13)
project(DuckOS
    LANGUAGES CXX ASM
    VERSION 0.1.0
    DESCRIPTION "DuckOS is custom OS written in C++ for fun"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# files
file(GLOB_RECURSE CPP_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} src/*.cpp)
file(GLOB_RECURSE ASM_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} src/*.asm)

add_executable(DuckOS ${CPP_SRCS} ${ASM_SRCS})

# asm
set_source_files_properties(${ASM_SRCS} PROPERTIES LANGUAGE ASM)
set(CMAKE_ASM_COMPILER nasm)
set(CMAKE_ASM_FLAGS "-f elf32")
set(CMAKE_ASM_COMPILE_OBJECT "<CMAKE_ASM_COMPILER> <FLAGS> -o <OBJECT> <SOURCE>")

# C++
set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O -Wall -Wextra -fno-rtti -fno-exceptions -nostdlib -ffreestanding -target i386-none-elf")

# linker
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/asm/linker.ld)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_options(${PROJECT_NAME} PRIVATE LINKER:-T ${LINKER_SCRIPT} -nostdlib)

target_include_directories(${PROJECT_NAME} PRIVATE include)
