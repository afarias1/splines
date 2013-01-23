cmake_minimum_required(VERSION 2.8.0)

#-std=c++0x option allows assignment of structs
#using ={....} notation without warning. 
#Handy for xyz, rgb tuples.
set(CMAKE_CXX_FLAGS "-g -Wall")

find_package(PNG REQUIRED)

#get symlink_data macro
include(${CMAKE_SOURCE_DIR}/cmake_modules/helpers.cmake)

add_subdirectory(w01-intro)

