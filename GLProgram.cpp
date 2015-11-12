#include "GLProgram.h"

GLProgram::GLProgram(std::vector<GLuint> shaderList){
	shaderProgram = glCreateProgram();
	for(auto s:shaderList){
		glAttachShader(shaderProgram,s);
	}
	glLinkProgram(shaderProgram);
	GLint status;
	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&status);
	
	if(status == GL_FALSE){
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH,&infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength+1];
		glGetProgramInfoLog(shaderProgram,infoLogLength,NULL,strInfoLog);
		fprintf(stderr,"Linker Failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}
GLuint GLProgram::getProgram(){
return shaderProgram;
}
GLProgram::operator GLuint(){
	return shaderProgram;
}
