cmake_minimum_required(VERSION 3.20)
project(wet2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(wet2
        Customer.cpp
        Customer.h
        Record.cpp
        Record.h
        recordsCompany.h
        utilesWet2.h recordsCompany.cpp Hash.h UnionFind.h)
