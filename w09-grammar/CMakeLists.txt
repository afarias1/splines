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
  vshader2.glsl
  fshader2.glsl
)

SET(MYLIBS ${EXT_LIBS} libcommon common_rgb common_noise)

ADD_EXECUTABLE(gramtest ${SRC} ${SHDRS} ${MYQTFILES} ${SHADERS})

TARGET_LINK_LIBRARIES(gramtest ${EXT_LIBS} libcommon)

symlink_data(grammar_shaders *.glsl)
symlink_data(grammar_data data)



