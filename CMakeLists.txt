cmake_minimum_required(VERSION 3.20)

project(logger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME} STATIC
        include/logger.hpp
        source/logger.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC include)