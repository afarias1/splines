find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

find_package(CUDA QUIET REQUIRED) #Any version OK
# find_package(CUDA 4.2 EXACT QUIET REQUIRED)

cuda_include_directories(${CUDA_INC} ${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${CUDA_SDK}/lib/)

set(HDRS book.h cpu_anim.h cpu_bitmap.h gl_helper.h gpu_anim.h
  timer.h)

cuda_add_library(mycuda13 timer.h book.h book.cu timer.cu)

set(GPROG heat)

foreach(PROG ${GPROG})
  cuda_add_executable(${PROG} ${PROG}.cu ${HDRS})
  target_link_libraries(${PROG} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m mycuda13)
endforeach()

# Add a special target to clean nvcc generated files.
#cuda_build_clean_target()
