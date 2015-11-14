#ifndef _GLAPP
#define _GLAPP
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>
#include <functional>

extern char** dummy;
class App{
	protected:
		GLFWwindow* window;
		float startTime;
		float elapsedTime;
		// Objects...
	public:
		App(int argc=0, char** argv=dummy);
		void run();
		void setKey(GLFWkeyfun key);
		void setMouse(GLFWcursorposfun mouse); 
		virtual void display()=0;
		virtual void init()=0;
		~App();
};
#endif
