cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(cpp_service CXX C)

find_package(Git REQUIRED)
find_package(Threads REQUIRED)
find_package(Protobuf REQUIRED)

# compiler
message(STATUS "compiler: ${CMAKE_CXX_COMPILER}, "
        "version: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# CMAKE_BUILD_TYPE
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel"
      FORCE)
endif()

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O2 -Wall -g -ggdb -fno-omit-frame-pointer -fdiagnostics-color=always -DRAPIDJSON_HAS_STDSTRING=1 -DSPDLOG_FMT_EXTERNAL=On")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall -g -ggdb -fno-omit-frame-pointer -fdiagnostics-color=always -DRAPIDJSON_HAS_STDSTRING=1 -DTHREADED -DSPDLOG_FMT_EXTERNAL=On")

set(THIRD_PARTY_PATH ${CMAKE_BINARY_DIR}/third_party)
set(THIRD_PARTY_BUILD_TYPE RELEASE)

# extern lib
# include(brpc)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
message(STATUS "src: ${CMAKE_CURRENT_SOURCE_DIR}/src")

add_definitions(-DGLOG_CUSTOM_PREFIX_SUPPORT)

add_subdirectory(src)