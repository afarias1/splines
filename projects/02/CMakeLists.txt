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

set(LIBHDRS drawable.h triangle.h)
set(LIBSRC drawable.cpp triangle.cpp )
add_library(proj2 ${LIBHDRS} ${LIBSRC})

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

ADD_EXECUTABLE(drawShapes ${SRC} ${LIBHDRS} ${MYQTFILES} ${SHADERS})

TARGET_LINK_LIBRARIES(drawShapes proj2 ${EXT_LIBS})

symlink_data(proj2_shaders *.glsl)


