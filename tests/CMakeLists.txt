Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview4
)
FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 20)

# files
file(GLOB_RECURSE CPP_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)

add_executable(tests ${CPP_SRCS})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain DuckSTD)
