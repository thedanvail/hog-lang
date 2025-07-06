cmake_minimum_required(VERSION 3.15)
project(hogc VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- LLVM ---
find_package(LLVM 19.1.4 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# --- LLD ---
get_filename_component(LLVM_PREFIX ${LLVM_DIR} DIRECTORY)  # /usr/lib/llvm-19
set(LLVM_LIBDIR "${LLVM_PREFIX}/lib")

# Manually point at the .a files
set(LLD_ELF_LIB    "${LLVM_LIBDIR}/liblldELF.a")
set(LLD_COMMON_LIB "${LLVM_LIBDIR}/liblldCommon.a")

foreach(_lib ${LLD_ELF_LIB} ${LLD_COMMON_LIB})
  if(NOT EXISTS "${_lib}")
    message(FATAL_ERROR "Required LLD archive not found: ${_lib}")
  endif()
endforeach()

message(STATUS "Using LLD static archives:")
message(STATUS "  ELF  = ${LLD_ELF_LIB}")
message(STATUS "  Common = ${LLD_COMMON_LIB}")

# Gather source files
file(GLOB_RECURSE SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Gather include directories from the "include" folder
file(GLOB SUBDIRS RELATIVE "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/include/*"
)

set(INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")

foreach(subdir ${SUBDIRS})
  if (IS_DIRECTORY "${PROJECT_SOURCE_DIR}/include/${subdir}")
    list(APPEND INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include/${subdir}")
  endif()
endforeach()

# Add executable and specify include directories target-specifically
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE SYSTEM ${LLVM_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${LLVM_DEFINITIONS})
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    ${LLVM_LIBRARIES}
    ${LLD_ELF_LIB}             # lld’s ELF driver
    ${LLD_COMMON_LIB}          # lld’s common support code
    pthread                    # sometimes needed by lld
)
target_link_libraries(${PROJECT_NAME} PRIVATE LLVM)
target_compile_options(${PROJECT_NAME} PRIVATE -Wpedantic)

