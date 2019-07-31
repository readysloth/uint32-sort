cmake_minimum_required(VERSION 3.13..3.15)

SET(PROJECT_NAME "uint32sort")
project(${PROJECT_NAME} VERSION 0.01 
        DESCRIPTION "Project for sorting arbitrary files, which contain uint32_t values"
        LANGUAGES CXX)


file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You should not build in a source directory (or any directory with CMakeLists.txt file).
                         Please, make 'build' subdirectory.")
endif()

include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/src")
add_executable(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/src/main.cpp")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/sort_lib/")


target_link_libraries(${PROJECT_NAME} PRIVATE SortCore)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)


