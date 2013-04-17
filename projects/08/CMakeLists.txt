# Note set CUDA_BUILD_EMULATION to OFF to enable Device mode compilation.
#set(CUDA_SDK /usr/local/src/NVIDIA_CUDA_SDK)
#set(CUDA_INC ${CUDA_SDK}/common/inc/)

find_package(CUDA QUIET REQUIRED) #Any version OK

cuda_include_directories(${CUDA_INC} ${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${CUDA_SDK}/lib/)

set(HDRS book.h timer.h)

cuda_add_library(cuda08 timer.h book.h book.cu timer.cu)

set(EASYPROGS dot_test maxval)

foreach(PROG ${EASYPROGS})
 cuda_add_executable(${PROG} ${PROG}.cu ${HDRS})
 target_link_libraries(${PROG} cuda08)
endforeach()

