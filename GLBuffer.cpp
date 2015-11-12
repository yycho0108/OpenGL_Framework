#include "GLBuffer.h"

void deleteBuffer(void* d){
	glDeleteBuffers(1,(GLuint*)d);
	free(d);
}

GLBuffer::GLBuffer():data{nullptr}{
	obj.reset(static_cast<GLuint*>(malloc(sizeof(GLuint))),deleteBuffer);
};


GLBuffer::GLBuffer(void* data, GLenum target, int size,
		int typeSize, int elemSize):obj{nullptr},target{target},size{size},typeSize{typeSize},count{size/typeSize},elemSize{elemSize},data{nullptr}{
		auto d = malloc(size);
		auto i = malloc(1*sizeof(GLuint));
		this->obj.reset((GLuint*)i,deleteBuffer);
		this->data.reset(d,free);
		memcpy(this->data.get(),data,size);
		
		//unsigned short* rawData = (unsigned short*)this->data.get();
		//for(int i=0;i<this->count;++i){
		//		std::cout << rawData[i] << ',';
		//	}
		//std::cout << std::endl;
		glGenBuffers(1,this->obj.get());
		glBindBuffer(target,getObj());

		glBufferData(target,size,this->data.get(),GL_STATIC_DRAW); //FOR NOW
		this->count = size/typeSize;
	}
void GLBuffer::update(void* data){
			memcpy(this->data.get(),data,size);	
			glBindBuffer(target,getObj());
			glBufferSubData(target,0,size,data);
			glBindBuffer(target,0);
}
void GLBuffer::apply(){
	glBindBuffer(target,getObj());
}
std::shared_ptr<void> GLBuffer::getData(){return data;}
int GLBuffer::getSize(){return size;}
int GLBuffer::getElemSize(){return elemSize;}
GLuint GLBuffer::getObj(){return *obj.get();}

GLBuffer::~GLBuffer(){
}
