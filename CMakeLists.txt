cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(cpp_service CXX C)

find_package(Git REQUIRED)
find_package(GFLAGS REQUIRED)
find_package(Threads REQUIRED)
find_package(Protobuf REQUIRED)

# compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # require at least gcc 4.8
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(FATAL_ERROR "GCC is too old, please install a newer version supporting C++11")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # require at least clang 3.3
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3)
        message(FATAL_ERROR "Clang is too old, please install a newer version supporting C++11")
    endif()
else()
    message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang and GCC.")
endif()

message(STATUS "compiler: ${CMAKE_CXX_COMPILER}, "
        "version: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(THIRD_PARTY_PATH ${CMAKE_BINARY_DIR}/third_party)
set(THIRD_PARTY_BUILD_TYPE RELEASE)

# extern lib
include(brpc)

add_subdirectory(src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

message(STATUS "src: ${CMAKE_CURRENT_SOURCE_DIR}/src")