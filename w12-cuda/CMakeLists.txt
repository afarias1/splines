find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Note set CUDA_BUILD_EMULATION to OFF to enable Device mode compilation.
#set(CUDA_SDK /usr/local/src/NVIDIA_CUDA_SDK)
#set(CUDA_INC ${CUDA_SDK}/common/inc/)

find_package(CUDA QUIET REQUIRED) #Any version OK
# find_package(CUDA 4.2 EXACT QUIET REQUIRED)

if (CUDA_FOUND)
   message("CUDA found")
else()
   message("CUDA not found")
endif()

cuda_include_directories(${CUDA_INC} ${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${CUDA_SDK}/lib/)

set(HDRS book.h cpu_anim.h cpu_bitmap.h gl_helper.h gpu_anim.h
  timer.h)

cuda_add_library(mycuda timer.h book.h book.cu timer.cu)

set(EASYPROGS dot)

foreach(PROG ${EASYPROGS})
 cuda_add_executable(${PROG} ${PROG}.cu ${HDRS})
 target_link_libraries(${PROG} mycuda)
endforeach()

set(GPROG ripple shared_bitmap)

foreach(PROG ${GPROG})
  cuda_add_executable(${PROG} ${PROG}.cu ${HDRS})
  target_link_libraries(${PROG} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m mycuda)
endforeach()

# Add a special target to clean nvcc generated files.
#cuda_build_clean_target()
