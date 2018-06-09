cmake_minimum_required(VERSION 3.10)
project(ESIProj)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(ESIProj main.cpp Gtk/DirWindow.cpp Gtk/DirWindow.h Utils/DirectoryManager.cpp Utils/DirectoryManager.h Utils/DirectoryEntry.cpp Utils/DirectoryEntry.h Gtk/DirBox.cpp Gtk/DirBox.h)
#add_custom_command(TARGET ESIProj POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${GTKMM_LIBRARY_DIRS}" ${PROJECT_BINARY_DIR}/libs)

target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})