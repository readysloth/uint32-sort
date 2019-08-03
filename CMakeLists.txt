cmake_minimum_required(VERSION 3.15)

SET(PROJECT_NAME "uint32sort")
project(${PROJECT_NAME} VERSION 0.01 
        DESCRIPTION "Project for sorting arbitrary files, which contain uint32_t values"
        LANGUAGES CXX)


file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You should not build in a source directory (or any directory with CMakeLists.txt file). Please, make 'build' subdirectory.")
endif()

include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/src")

message("[running ${CMAKE_COMMAND}]")
exec_program("${CMAKE_COMMAND} ${PROJECT_SOURCE_DIR}/src")
