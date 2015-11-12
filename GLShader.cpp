#include "GLShader.h"
std::string fileToSrc(const char* fileName){

	std::string srcString;
	std::string sLine;
	std::ifstream f_in{fileName};
	
	while(std::getline(f_in,sLine)){
		srcString += '\n';
		srcString += sLine;
	}
	f_in.close();

	return srcString;
}

GLShader::GLShader(GLenum type, const std::string& srcString){
	shader = glCreateShader(type);
	const char* srcStr = srcString.c_str();
	glShaderSource(shader,1,&srcStr,NULL);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
	if(status == GL_FALSE){
		GLint logLen;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&logLen);
		GLchar* infoLog = new GLchar[logLen+1];
		glGetShaderInfoLog(shader,logLen,NULL,infoLog);
		const char* shaderType = NULL;
		switch(type){
			case GL_VERTEX_SHADER: shaderType = "Vertex";
					 break;
			case GL_FRAGMENT_SHADER: shaderType = "Fragment";
					 break;
			case GL_GEOMETRY_SHADER: shaderType = "Geometry";
					 break;
			default: shaderType = "Wrong Type";
					 break;
		}
		std::cerr << "Compile Failure in " << shaderType << " Shader; Log:" << infoLog;
		delete[] infoLog;
	}
};

GLShader::GLShader(GLenum type, const char* fileName)
:GLShader(type,fileToSrc(fileName)){
}

GLuint GLShader::getShader(){
	return shader;
}
GLShader::operator GLuint(){return shader;}
GLShader::~GLShader(){
	glDeleteShader(shader);
}

