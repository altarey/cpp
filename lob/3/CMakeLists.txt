cmake_minimum_required(VERSION 3.28)
project(lobmt)

set(CMAKE_CXX_STANDARD 20)

add_executable(c__ main.cpp
        c_allocator.h
        cpp_allocator.h
        log.h
        order.h
        limitorderbook.h)