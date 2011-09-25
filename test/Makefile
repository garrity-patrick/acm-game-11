GLFW_INSTALL=/usr/local
#GLFW_INCLUDE=$(GLFW_INSTALL)/include
GLFW_LIB=$(GLFW_INSTALL)/lib

GL_LIB=/usr/lib

IMMORAL_INSTALL=/home/garrity/projects/opengl/acm
IMMORAL_INCLUDE=$(IMMORAL_INSTALL)/include
IMMORAL_LIB=$(IMMORAL_INSTALL)/lib

CC=g++
CFLAGS=-Wall -Iinclude -I$(IMMORAL_INCLUDE)
LFLAGS=-Wall -L$(IMMORAL_LIB) -L$(GLFW_LIB) -L$(GL_LIB) -limmoral -lGL -lGLU -lglfw

default: test

.PHONY : clean
clean:
	rm -f build/*.o bin/test

.PHONY : compile
compile: build/test.o

build/test.o: src/test.cpp
	$(CC) $(CFLAGS) -c src/test.cpp -o build/test.o

test: build/test.o
	$(CC) $(LFLAGS) -o bin/test build/test.o
