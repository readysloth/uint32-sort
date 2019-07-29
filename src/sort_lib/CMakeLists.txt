cmake_minimum_required(VERSION 3.1.0)

SET(PROJECT_NAME "SortCore")
project(${PROJECT_NAME} VERSION 0.01 LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR}/../../include ${PROJECT_SOURCE_DIR})

file(GLOB SRC_LIB_FILES *.cpp)

add_library(${PROJECT_NAME} ${SRC_LIB_FILES})
find_package(OpenMP REQUIRED) 

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

