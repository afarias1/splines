INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} .)

set(SHDRS sphere.h square.h)
set(SSRC sphere.cpp square.cpp)

add_library(libcommon ${SHDRS} ${SSRC})

set(CLRHDRS png_reader.h png_writer.h
  rgbColor.h rgbImage.h)
set(CLRSRC png_reader.cpp png_writer.cpp rgbImage.cpp)
add_library(common_rgb ${CLRHDRS} ${CLRSRC})


