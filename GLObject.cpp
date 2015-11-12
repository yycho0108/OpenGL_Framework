#include "GLObject.h"

GLObject::GLObject(){
		glGenVertexArrays(1,&vao);
}

	void GLObject::push(const GLAttrib& attrib){
		Attribs.push_back(attrib);
	}	
	void GLObject::push(const GLBuffer& buffer){
		Buffers.push_back(buffer);
	}
	void GLObject::apply(){
		glBindVertexArray(vao);
		for(auto& a:Attribs){
			a.apply();
		}
		for(auto& b:Buffers){
			b.apply();
		}
	}
	void GLObject::draw(){
		if(Buffers.size() > 0){
			glDrawElements(GL_TRIANGLES,Buffers[0].getSize(),GL_UNSIGNED_SHORT,0);
			//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
		}
		//glDrawArrays(GL_TRIANGLES,0,3);
	}

GLObject::~GLObject(){};
