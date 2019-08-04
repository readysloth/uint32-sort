
cmake_minimum_required(VERSION 3.15)

SET(PROJECT_NAME "uint32_sort_gui")
project("${PROJECT_NAME}" VERSION 0.01 
        DESCRIPTION "Project for sorting arbitrary files, which contain uint32_t values"
        LANGUAGES CXX)

#if(EXISTS "${LOC_PATH}")
#    message(FATAL_ERROR "You should not build in a source directory (or any directory with CMakeLists.txt file). Please, make 'build' subdirectory.")
#endif()

file(GLOB SRC_FILES *.cpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../include")
find_package(Qt5 COMPONENTS 
             Core 
             Gui
             Qml
             Quick
             QuickControls2
             Widgets
             REQUIRED
             )

include_directories("${INCLUDE_DIR}" "${PROJECT_SOURCE_DIR}")
add_subdirectory("${PROJECT_SOURCE_DIR}/sort_lib/")

add_executable("${PROJECT_NAME}" "${INCLUDE_DIR}/lib_controller.hpp" "${SRC_FILES}" "qml.qrc")


target_link_libraries("${PROJECT_NAME}"
                      PUBLIC
                      Qt5::Core
                      Qt5::Gui
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::QuickControls2
                      Qt5::Widgets
                      SortCore
                      )

