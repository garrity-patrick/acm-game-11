GLFW_INSTALL=/usr/local
GLFW_INCLUDE=$(GLFW_INSTALL)/include
GLFW_LIB=$(GLFW_INSTALL)/lib

GL_LIB=/usr/lib

SONAME=libimmoral.so
CC=g++
CFLAGS=-Wall -Iinclude -fPIC
LFLAGS=-Wall -L$(GLFW_LIB) -L$(GL_LIB) -lGL -lGLU -lglfw -shared -Wl,-soname,$(SONAME)

TARGETS=\
build/immoral/game.o \
build/immoral/ppm.o \
build/immoral/vector2.o

################################################################################
### Top-Level Targets
################################################################################
default: lib

.PHONY : clean
clean:
	rm -f build/*.o build/immoral/*.o lib/*.so lib/*.a

.PHONY : compile
compile: $(TARGETS)

.PHONY : lib
lib: lib/libimmoral.so

################################################################################
### Compile Targets: Main
################################################################################
build/immoral/game.o: src/immoral/game.cpp include/immoral/game.hpp
	$(CC) $(CFLAGS) -c src/immoral/game.cpp -o build/immoral/game.o
	
################################################################################
### Compile Targets: Math
################################################################################
build/immoral/vector2.o: src/immoral/vector2.cpp include/immoral/vector2.hpp
	$(CC) $(CFLAGS) -c src/immoral/vector2.cpp -o build/immoral/vector2.o

################################################################################
### Compile Targets: Utility
################################################################################
build/immoral/ppm.o: src/immoral/ppm.cpp include/immoral/ppm.hpp
	$(CC) $(CFLAGS) -c src/immoral/ppm.cpp -o build/immoral/ppm.o

################################################################################
### Link Targets
################################################################################
lib/libimmoral.so: compile
	$(CC) $(LFLAGS) -o lib/$(SONAME) $(TARGETS)
