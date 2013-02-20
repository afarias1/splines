INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} .)

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

set(SHDRS sphere.h square.h)
set(SSRC sphere.cpp square.cpp)

add_library(libsphere ${SHDRS} ${SSRC})

ADD_EXECUTABLE(sphere ${SRC} ${SHDRS} ${MYQTFILES} ${SHADERS})

TARGET_LINK_LIBRARIES(sphere ${EXT_LIBS} libsphere)

symlink_data(sphere_shaders *.glsl)
symlink_data(sphere_png data)


