find_package(GLUT REQUIRED)

set(PROGS example1)

symlink_data(shader02 *.glsl)

foreach(PROG ${PROGS})
  add_executable(${PROG} ${PROG}.cpp)
  target_link_libraries(${PROG} 
  ${GLUT_glut_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} common)
endforeach()
