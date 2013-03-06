include_directories(PNG_INCLUDE_DIR)
find_package(PNG REQUIRED)

set(HDRS common.h png_reader.h png_writer.h
  rgbColor.h rgbImage.h ray.h shape.h 
  material.h view.h light.h
  parser.h raytracer.h
)

set(LIBSRCS common.cpp png_reader.cpp png_writer.cpp rgbImage.cpp
  ray.cpp parser.cpp raytracer.cpp
)
   
add_library(rtrace ${HDRS} ${LIBSRCS})

#  add these to library above when ready
#  sphere.h sphere.cpp
#  rectangle.h rectangle.cpp
#  triangle.h triangle.cpp


add_executable(makescene ${HDRS} makescene.cpp)

set(ALLLIBS rtrace ${EXT_LIBS} ${PNG_LIBRARIES})
target_link_libraries(makescene ${ALLLIBS})

symlink_data(raytracer *.txt)

