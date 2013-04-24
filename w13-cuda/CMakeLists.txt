find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

find_package(CUDA QUIET REQUIRED) #Any version OK
# find_package(CUDA 4.2 EXACT QUIET REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} .)

cuda_include_directories(${CUDA_INC} ${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${CUDA_SDK}/lib/)

set(HDRS book.h cpu_anim.h cpu_bitmap.h gl_helper.h gpu_anim.h
  timer.h)

cuda_add_library(mycuda13 
  cudahelpers.h timer.h book.h 
  cudahelpers.cu book.cu timer.cu)

set(GPROG heat)

foreach(PROG ${GPROG})
  cuda_add_executable(${PROG} ${PROG}.cu ${HDRS})
  target_link_libraries(${PROG} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m mycuda13)
endforeach()

#QT headers requiring MOC (meta object compiler)
set(QTHDRS 
  mainwindow.h 
  mypanelopengl.h
  )

#window design files
set(QTFORMS mainwindow.ui)

#Run qt tools to auto generate C++ compatible files
QT4_WRAP_CPP(QTHDRS_MOC ${QTHDRS})
QT4_WRAP_UI(QTFORMS_HDRS ${QTFORMS})
SET(MYQTFILES ${QTHDRS_MOC} ${QTFORMS_HDRS})

#normal source files
set(SRC 
  main.cpp 
  mainwindow.cpp 
  mypanelopengl.cpp
)

set(SHADERS
  vshader.glsl
  fshader.glsl
)

ADD_EXECUTABLE(interop ${SRC} ${SHDRS} ${MYQTFILES} ${SHADERS})

TARGET_LINK_LIBRARIES(interop ${EXT_LIBS} libcommon mycuda13)

symlink_data(interop_shaders *.glsl)
symlink_data(interop_data data)

cuda_add_executable(julia_gpu2 julia_gpu.cu ${HDRS})
target_link_libraries(julia_gpu2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m mycuda13)


