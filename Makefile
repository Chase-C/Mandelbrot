UNAME		:= $(shell uname)
GCC			= g++ -std=c++11 -O0

ifeq($(UNAME),Linux)
LIBS		= `pkg-config --cflags --libs allegro-5.0`
else
LIBS		= -lallegro-5.0.9-monolith-md
endif

SOURCES		= code/main.cpp code/Mandelbrot.cpp code/Thread.cpp code/Utils.cpp
EXECS		= Mandelbrot

${EXECS} : ${SOURCES}
	${GCC} -o ${EXECS} ${SOURCES} ${LIBS}

clean :
	- rm core

spotless : clean
	- rm ${EXECS}.exe
