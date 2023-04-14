# files
file(GLOB_RECURSE CPP_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} src/*.cpp)

add_library(DuckSTD ${CPP_SRCS})

# C++
set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_FLAGS "-O0 -g -ggdb3 -Wall -Wextra -std=c++20 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-PIE -target x86_64-none-elf -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fcolor-diagnostics")

target_include_directories(DuckSTD PUBLIC include)
