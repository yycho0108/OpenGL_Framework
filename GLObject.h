#ifndef _GLOBJECT
#define _GLOBJECT
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
#include "GLBuffer.h"
#include "GLAttrib.h"

class GLObject{
	private:
		GLuint vao;
		std::vector<GLAttrib> Attribs;
		std::vector<GLBuffer> Buffers;//namely, vertex Indices
	public:	
		GLObject();
		void push(const GLAttrib& attrib);
		void push(const GLBuffer& buffer);
		void apply();
		void draw();
		//update
		~GLObject();
		//VAO
		//
};

#endif
