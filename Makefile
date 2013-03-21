GCC			= g++ -std=c++11 -O3
LIBS		= -lallegro-5.0.9-monolith-md
SOURCES		= code/main.cpp code/Mandelbrot.cpp code/Thread.cpp code/Utils.cpp
EXECS		= Mandelbrot

${EXECS} : ${SOURCES}
	${GCC} -o ${EXECS} ${SOURCES} ${LIBS}

clean :
	- rm core

spotless : clean
	- rm ${EXECS}.exe
