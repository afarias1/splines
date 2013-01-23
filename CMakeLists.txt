cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_FLAGS "-g -Wall")

#find PNG include directories/libraries
#/usr/share/cmake-2.8/Modules/FindPNG.cmake
find_package(PNG REQUIRED)

#get symlink_data macro
include(${CMAKE_SOURCE_DIR}/cmake_modules/helpers.cmake)

add_subdirectory(w01-intro)

