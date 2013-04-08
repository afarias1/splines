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
include_directories(./)
add_subdirectory(w01-intro)
add_subdirectory(w02-opengl)
add_subdirectory(w03-geometry)
add_subdirectory(w04-colorVBO)
add_subdirectory(w05-3D)
add_subdirectory(projects)
add_subdirectory(common)
add_subdirectory(w07-lighting)
add_subdirectory(w08-noise)
add_subdirectory(w09-grammar)
add_subdirectory(w10-particles)
add_subdirectory(w11-cuda)

