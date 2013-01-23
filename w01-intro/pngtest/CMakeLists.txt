#find_package(PNG REQUIRED)

include_directories(PNG_INCLUDE_DIRS)

#-std=c++0x allows assignment of structs using = {...} syntax
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")


#Header files for our rgb library
set(RGBHDRS rgbColor.h rgbImage.h png_reader.h png_writer.h)
#Source files for our rgb library
set(RGBSRC rgbImage.cpp png_reader.cpp png_writer.cpp)

#create our own library librgb
add_library(rgb ${RGBHDRS} ${RGBSRC})


#Compile, but do not link executable test_rgb
add_executable(test_rgb test_rgb.cpp ${RGBHDRS})

#Link the libraries
target_link_libraries(test_rgb rgb ${PNG_LIBRARIES})

#Symlink data files into build directory
symlink_data(test_rgb *.png)
