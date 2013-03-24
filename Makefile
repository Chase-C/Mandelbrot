GCC			= g++ -std=c++11 -O0
LIBS		= `pkg-config --cflags --libs allegro-5.0`
SOURCES		= code/main.cpp code/Mandelbrot.cpp code/Thread.cpp code/Utils.cpp
EXECS		= Mandelbrot

${EXECS} : ${SOURCES}
	${GCC} -o ${EXECS} ${SOURCES} ${LIBS}

clean :
	- rm core

spotless : clean
	- rm ${EXECS}.exe
