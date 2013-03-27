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
  parser.cpp
  plant.cpp
)

set(SHADERS
  vshader.glsl
  fshader.glsl
)

set(TXTINPUT myplant.txt)

set(HDRS ${SHDRS} ${MYQTFILES} parser.h production.h plant.h)

SET(MYLIBS ${EXT_LIBS} libcommon common_rgb common_noise)

ADD_EXECUTABLE(growplants ${SRC} ${HDRS} ${SHADERS} ${TXTINPUT})

TARGET_LINK_LIBRARIES(growplants ${EXT_LIBS} libcommon)

symlink_data(p07_shaders *.glsl)
symlink_data(p07_data data)
symlink_data(p07_input ${TXTINPUT})



