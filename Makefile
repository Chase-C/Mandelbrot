GCC			= g++ -std=c++11 -O3
SOURCES		= main.cpp Mandelbrot.cpp Utils.cpp
EXECS		= Mandelbrot

${EXECS} : ${SOURCES}
	${GCC} $< -o $@

clean :
	- rm core

spotless : clean
	- rm ${EXECS}.exe
