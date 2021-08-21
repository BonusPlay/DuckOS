set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# files
file(GLOB_RECURSE CPP_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} src/*.cpp)
file(GLOB_RECURSE ASM_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} src/*.asm)

add_executable(DuckOS ${CPP_SRCS} ${ASM_SRCS})

# asm
set_source_files_properties(${ASM_SRCS} PROPERTIES LANGUAGE ASM)
set(CMAKE_ASM_COMPILER nasm)
set(CMAKE_ASM_FLAGS "-f elf64 -g")
set(CMAKE_ASM_COMPILE_OBJECT "<CMAKE_ASM_COMPILER> <FLAGS> -o <OBJECT> <SOURCE>")

# C++
set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -std=c++20 -fno-rtti -fno-exceptions -nostdlib -ffreestanding -fno-PIE -target x86_64-none-elf -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -ggdb3")

# linker
set(CMAKE_LINKER ld.lld)
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/src/asm/linker.ld)
set_target_properties(DuckOS PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
target_link_options(DuckOS PRIVATE LINKER: --script ${LINKER_SCRIPT} -nostdlib --no-pie)
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

#set(ARCHDIR "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/DuckOS.dir/src/asm")
#set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> ${ARCHDIR}/crtbegin.asm.o <OBJECTS> -o <TARGET> <LINK_LIBRARIES> ${ARCHDIR}/crtend.asm.o")

# DuckSTD global int types
target_compile_definitions(DuckOS PRIVATE DSTD_GLOBAL_INTS=1)

target_include_directories(DuckOS PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(DuckOS DuckSTD)
