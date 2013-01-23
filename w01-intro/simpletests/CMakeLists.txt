
#Compile a simple executable
add_executable(helloCS40 helloCS40.cpp)

set(MTESTS mathTest1 mathTest2)

foreach(PROG ${MTESTS})
 add_executable(${PROG} ${PROG}.cpp)
endforeach(PROG)

