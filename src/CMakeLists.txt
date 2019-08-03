
cmake_minimum_required(VERSION 3.15)

SET(PROJECT_NAME "uint32_sort_gui")
project("${PROJECT_NAME}" VERSION 0.01 
        DESCRIPTION "Project for sorting arbitrary files, which contain uint32_t values"
        LANGUAGES CXX)

#if(EXISTS "${LOC_PATH}")
#    message(FATAL_ERROR "You should not build in a source directory (or any directory with CMakeLists.txt file). Please, make 'build' subdirectory.")
#endif()

file(GLOB SRC_FILES *.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS 
             Core 
             Gui
             Qml
             Quick
             QuickControls2
            
             REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/../include" "${PROJECT_SOURCE_DIR}")
add_subdirectory("${PROJECT_SOURCE_DIR}/sort_lib/")

add_executable("${PROJECT_NAME}" "${SRC_FILES}" "qml.qrc")


target_link_libraries("${PROJECT_NAME}"
                      PUBLIC
                      Qt5::Core
                      Qt5::Gui
                      Qt5::Qml
                      Qt5::Quick
                      SortCore
                      )

set_target_properties("${PROJECT_NAME}" PROPERTIES
                      CXX_STANDARD 11
                      CXX_STANDARD_REQUIRED ON)
