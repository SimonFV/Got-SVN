cmake_minimum_required(VERSION 3.8)

project(client)

set(CMAKE_CXX_STANDARD_REQUIRED 11)

set(src
    src/main.cpp
)

set(head
    include/client.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/include/)


#Logging
add_subdirectory(spdlog)
add_subdirectory(cpr)

add_executable(run ${src} ${head})

target_link_libraries(run spdlog cpr::cpr)