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

class App{
	private:
		GLFWwindow* window;
		float startTime;
		float elapsedTime;
		std::function<void()> init;
		std::function<void()> display;
		// Objects...
	public:
		App(int argc, char** argv);
		void run();
		void setInit(std::function<void()> init);
		void setDisplay(std::function<void()> display);
		~App();
};
#endif
