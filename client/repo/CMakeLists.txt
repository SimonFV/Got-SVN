cmake_minimum_required(VERSION 3.8)

project(repo)

set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(src
    main.cpp
)

add_executable(test ${src})