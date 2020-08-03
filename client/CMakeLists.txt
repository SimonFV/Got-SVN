cmake_minimum_required(VERSION 3.8)

project(client)

set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(src
    src/main.cpp
    src/diff.cpp
    src/huffman.cpp
    src/md5.cpp
)

set(head
    include/client.hpp
    include/huffman.hpp
    include/md5.h
)

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/src/)


#Logging
add_subdirectory(spdlog)
add_subdirectory(cpr)
add_subdirectory(jsoncons)

add_executable(got ${src} ${head})

target_link_libraries(got spdlog cpr::cpr jsoncons)