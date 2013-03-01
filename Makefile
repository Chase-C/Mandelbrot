GCC			= g++ -std=c++11 -O3
LIBS		= -lallegro-5.0.8-monolith-md
SOURCES		= main.cpp Mandelbrot.cpp Utils.cpp
EXECS		= Mandelbrot

${EXECS} : ${SOURCES}
	${GCC} -o ${EXECS} ${SOURCES} ${LIBS}

clean :
	- rm core

spotless : clean
	- rm ${EXECS}.exe
