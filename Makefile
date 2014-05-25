#OBJS specifies which files to compile as part of the project
#OBJS = src/Character.cpp src/Level.cpp src/main.cpp
OBJS = src/Character.cpp src/main.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# g 	 - compile with debug information
# Wall 	 - show all compiler warnings
# Wextra - show extra compiler warninres
COMPILER_FLAGS = -g -Wall -Wextra $(OPTFLAGS)

#LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = -lGL -lGLU -lglut
#SDL_STUFF = `/usr/local/bin/sdl2-config --libs --cflags`
#SDL_STUFF = `pkg-config --libs --cflags sdl2`
LINKER_FLAGS = -framework OpenGL -lSDL2 -lGLEW

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = engine

#This is the target that compiles our executable
all : clean $(OBJS)
	$(CC) $(OBJS) \
	$(INCLUDE_PATHS) $(LIBRARY_PATHS) \
	$(COMPILER_FLAGS) $(LINKER_FLAGS) \
	-o $(OBJ_NAME)

clean:
	rm -f $(OBJ_NAME)

# http://astyle.sourceforge.net/astyle.html
style:
	astyle --options=.astylerc `ls src/*.h src/*.cpp`

# http://cppcheck.sourceforge.net/manual.html
lint:
	cppcheck --enable=all ./src

grind: all
	valgrind ./$(OBJ_NAME)
