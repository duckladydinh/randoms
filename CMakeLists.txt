cmake_minimum_required(VERSION 3.15)
project(algo_cpp)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE algo_lib_sources *.cpp EXCLUDE main.cpp)
include_directories (${PROJECT_SOURCE_DIR})
add_library(algo_lib ${algo_lib_sources} cpalgorithms/two_sat.cpp cpalgorithms/linear_sieve.cpp)

add_executable(algo_cpp main.cpp cpalgorithms/geometry.cpp cpalgorithms/persistent_treap.cpp cpalgorithms/cyclic_path.cpp init.h cpalgorithms/tarjan.cpp cpalgorithms/string_matching.cpp cpalgorithms/euler_path.cpp cpalgorithms/linear_congruences.cpp cpalgorithms/prime.cpp cpalgorithms/integer_ternary.cpp cpalgorithms/trick.cpp)
target_link_libraries(algo_cpp algo_lib)
