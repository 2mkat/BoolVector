cmake_minimum_required(VERSION 3.17)
project(bool_vector)

set(CMAKE_CXX_STANDARD 14)

add_library(bool_vector bool_l.cpp bool_l.h main.cpp)