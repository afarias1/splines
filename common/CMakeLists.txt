INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} .)

set(SHDRS sphere.h square.h)
set(SSRC sphere.cpp square.cpp)

add_library(libcommon ${SHDRS} ${SSRC})

