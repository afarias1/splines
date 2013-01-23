cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_FLAGS "-g -Wall")

set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules) #for FindGLEW.cmake

#find PNG include directories/libraries
#/usr/share/cmake-2.8/Modules/FindPNG.cmake
find_package(PNG REQUIRED)

FIND_PACKAGE(OpenGL REQUIRED) #for graphics
FIND_PACKAGE(Qt4 REQUIRED) #for window widgets
FIND_PACKAGE(GLEW REQUIRED)

#required CMake options for QT Apps
SET(QT_USE_QTOPENGL TRUE) #required for QT Apps using OPENGL
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

SET(EXT_LIBS ${QT_LIBRARIES} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

#get symlink_data macro
include(${CMAKE_SOURCE_DIR}/cmake_modules/helpers.cmake)

add_subdirectory(w01-intro)

