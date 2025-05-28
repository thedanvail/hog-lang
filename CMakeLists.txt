cmake_minimum_required(VERSION 3.15)
project(hogc VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gather source files
file(GLOB_RECURSE SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Gather include directories from the "include" folder
file(GLOB SUBDIRS RELATIVE "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/include/*"
)

set(INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include" 
    "${PROJECT_SOURCE_DIR}/include/arg_parser" 
    "${PROJECT_SOURCE_DIR}/vendor/utpp/include" 
    "${PROJECT_SOURCE_DIR}/src"
)

foreach(subdir ${SUBDIRS})
  if (IS_DIRECTORY "${PROJECT_SOURCE_DIR}/include/${subdir}")
    list(APPEND INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include/${subdir}")
  endif()
endforeach()

# Add executable and specify include directories target-specifically
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# Add compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-unused-includes)
target_compile_options(${PROJECT_NAME} PRIVATE -Wpedantic)

