cmake_minimum_required(VERSION 3.26)
project(University_Address_Book)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(University_Address_Book
        main.cpp
        main.h
        menu.cpp
        menu.h)
