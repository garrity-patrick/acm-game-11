GLFW_INSTALL=/usr/local
GLFW_INCLUDE=$(GLFW_INSTALL)/include
GLFW_LIB=$(GLFW_INSTALL)/lib

GL_LIB=/usr/lib

IMMORAL_INSTALL=..
IMMORAL_INCLUDE=$(IMMORAL_INSTALL)/include
IMMORAL_LIB=$(IMMORAL_INSTALL)/lib

CC=g++
CFLAGS=-Wall -Iinclude -I$(IMMORAL_INCLUDE) -I$(GLFW_INCLUDE)
LFLAGS=-Wall -L$(IMMORAL_LIB) -L$(GLFW_LIB) -L$(GL_LIB) -limmoral -lGL -lGLU -lglfw

OBJECTS=\
build/test.o \
build/multitexture.o

TESTS=\
bin/test \

default: link

.PHONY : clean
clean:
	rm -f build/*.o bin/*test*

.PHONY : compile
compile: $(OBJECTS)

.PHONY : link
link: compile $(TESTS)

build/test.o: src/test.cpp
	$(CC) $(CFLAGS) -c src/test.cpp -o build/test.o

build/datatype_test.o: src/datatype_test.cpp
	$(CC) $(CFLAGS) -c src/datatype_test.cpp -o build/datatype_test.o

build/multitexture.o: src/multitexture.cpp
	$(CC) $(CFLAGS) -c src/multitexture.cpp -o build/multitexture.o

bin/test: $(OBJECTS)
	$(CC) $(LFLAGS) -o bin/test $(OBJECTS)
