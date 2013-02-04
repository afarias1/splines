
set(HDRS vector3d.h)
set(SRC vector3d.cpp)

include_directories(./)

add_library(w03geom ${HDRS} ${SRC})

set(PROGS testvec3d)

foreach(PROG ${PROGS})
  add_executable(${PROG} ${PROG}.cpp ${HDRS} ${SRC})
  target_link_libraries(${PROG} w03geom m)
endforeach(PROG)
