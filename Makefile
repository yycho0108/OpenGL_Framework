CC = g++
FLAGS=-Wall -std=c++11
LIBS=-L/usr/lib -lglut -lGL -lGLU -lGLEW -lglfw3 -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -ldl -lpthread
INCS=-I/usr/include
TARGET = main
all: $(TARGET) 

$(TARGET): GLObject.o GLProgram.o GLShader.o GLBuffer.o GLAttrib.o GLUniform.o  App.o $(TARGET).cpp
	$(CC) $(FLAGS) $(INCS) $^ -o $@ $(LIBS) -ggdb
GLBuffer.o: GLBuffer.cpp
	$(CC) -c $(FLAGS) $(INCS) $^ -o $@ $(LIBS) -ggdb
GLAttrib.o: GLBuffer.o GLAttrib.cpp
	$(CC) -c $(FLAGS) $(INCS) $^ -o $@ $(LIBS) -ggdb
GLUniform.o: GLUniform.cpp
	$(CC) -c $(FLAGS) $(INCS) $^ -o $@ $(LIBS) -ggdb
GLObject.o: GLAttrib.o GLBuffer.o GLUniform.o GLObject.cpp
	$(CC) -c $(FLAGS) $(INCS) $^ -o $@ $(LIBS) -ggdb
GLProgram.o: GLProgram.cpp
	$(CC) -c $(FLAGS) $(INCS) $^ -o $@ $(LIBS) -ggdb
GLShader.o: GLShader.cpp
	$(CC) -c $(FLAGS) $(INCS) $^ -o $@ $(LIBS) -ggdb
App.o: App.cpp
	$(CC) -c $(FLAGS) $(INCS) $^ -o $@ $(LIBS) -ggdb

clean :
	rm GLBuffer.o
	rm GLAttrib.o
	rm GLObject.o
	rm GLProgram.o
	rm GLShader.o
	rm App.o
	rm $(TARGET)
