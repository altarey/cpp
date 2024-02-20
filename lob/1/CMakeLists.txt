cmake_minimum_required(VERSION 3.28)
project(lobbasic)

set(CMAKE_CXX_STANDARD 20)

add_executable(c__ main.cpp
        log.h
        order.h
        limitorderbook.h)