#ifndef _GLPROGRAM
#define _GLPROGRAM

#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>

class GLProgram{
	private:
		GLuint shaderProgram;
	public:
		GLProgram(std::vector<GLuint> shaderList);
		operator GLuint();
		GLuint getProgram();
};
#endif
