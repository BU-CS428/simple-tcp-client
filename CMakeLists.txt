cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(tcp_client)

add_compile_options(-Wall -Wextra -O2 -Wunused-parameter)

add_subdirectory(lib/spdlog)
add_subdirectory(src)
add_subdirectory(tests)