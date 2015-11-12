#include "GLAttrib.h"

GLAttrib::GLAttrib(float* data, int size, int elemSize, int loc)
		 :GLBuffer{data,GL_ARRAY_BUFFER,size,sizeof(float),elemSize}{
		 this->loc = loc; //attrib location
	}
void GLAttrib::apply(){
		GLBuffer::apply();
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc,elemSize,GL_FLOAT,GL_FALSE,0,0);
}

GLAttrib::~GLAttrib(){

}
