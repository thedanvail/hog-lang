cmake_minimum_required(VERSION 3.15)
project(hogc)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)
