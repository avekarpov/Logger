cmake_minimum_required(VERSION 3.20)

project(test_logger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
        main.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE ./libs)

target_link_libraries(${PROJECT_NAME}
        logger)
