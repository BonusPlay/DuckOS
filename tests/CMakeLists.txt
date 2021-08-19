Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)
FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 20)

add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain DuckSTD)

# DuckSTD global int types
#target_compile_definitions(tests PRIVATE DSTD_GLOBAL_INTS=0)
