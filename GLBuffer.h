#ifndef _GLBUFFER
#define _GLBUFFER
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

class GLBuffer{
	protected:
		std::shared_ptr<GLuint> obj;
		GLenum target;
		int size; //whole thing
		int typeSize; //type size
		int count;
		int elemSize; //one 'element', i.e. 3 floats per vertex
		std::shared_ptr<void> data;
	public:
		GLBuffer();
		GLBuffer(void* data, GLenum targ, int size, int typeSize, int elemSize);
		void update(void* data);
		void apply();
		std::shared_ptr<void> getData();
		int getSize();
		int getElemSize();
		GLuint getObj();
		~GLBuffer();
};
#endif

