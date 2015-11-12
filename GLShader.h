#ifndef _GLSHADER
#define _GLSHADER
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

class GLShader{
	private:
		GLuint shader;
	public:
		GLShader(GLenum type, const std::string& srcString);
		GLShader(GLenum type, const char* fileName);
		operator GLuint();
		GLuint getShader();
		~GLShader();
};
#endif
