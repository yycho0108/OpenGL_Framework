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
#include "../Downloads/glm/glm/glm.hpp"
#include "../Downloads/glm/glm/gtc/matrix_transform.hpp"
#include "../Downloads/glm/glm/gtc/type_ptr.hpp"

#define TRYGLFW



GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile){
	GLuint shader = glCreateShader(eShaderType);
	const char* strFileData = strShaderFile.c_str();
	glShaderSource(shader,1,&strFileData,NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
	if(status == GL_FALSE){
		GLint infoLogLength;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength+1];
		glGetShaderInfoLog(shader,infoLogLength,NULL,strInfoLog);
		const char *strShaderType = NULL;
		switch(eShaderType){
			case GL_VERTEX_SHADER: strShaderType = "vertex";
					       break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry";
						 break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment";
						 break;
		}
		fprintf(stderr,"Compile failure in %s shader:\n%s\n", strShaderType,strInfoLog);
		delete[] strInfoLog;
	}
	return shader;
}
GLuint CreateShaderFromFile(GLenum eShaderType, const char* fileName){	
	std::string srcString;
	std::string sLine;

	std::ifstream f_in{fileName};

	while (std::getline(f_in, sLine)){
		srcString += '\n';
		srcString += sLine;
	}
	return CreateShader(eShaderType,srcString.c_str());
}

const float vertexPositions[] = {
	-1,-1,-1,

	0.75f, 0.75f, 0.0f, 
	0.75f, -0.75f, 0.0f,
	-0.75f, -0.75f, 0.0f,
};
const float vertexColors[] = {
	1.0f,0.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
};
const unsigned short vCubeFace[] = {
  0,  1,  2,      0,  2,  3,    // front
  4,  5,  6,      4,  6,  7,    // back
  8,  9,  10,     8,  10, 11,   // top
  12, 13, 14,     12, 14, 15,   // bottom
  16, 17, 18,     16, 18, 19,   // right
  20, 21, 22,     20, 22, 23    // left
  };
float vCubePos[] = {
  // Front face
  -1.0, -1.0,  1.0,
   1.0, -1.0,  1.0,
   1.0,  1.0,  1.0,
  -1.0,  1.0,  1.0,
  
  // Back face
  -1.0, -1.0, -1.0,
  -1.0,  1.0, -1.0,
   1.0,  1.0, -1.0,
   1.0, -1.0, -1.0,
  
  // Top face
  -1.0,  1.0, -1.0,
  -1.0,  1.0,  1.0,
   1.0,  1.0,  1.0,
   1.0,  1.0, -1.0,
  
  // Bottom face
  -1.0, -1.0, -1.0,
   1.0, -1.0, -1.0,
   1.0, -1.0,  1.0,
  -1.0, -1.0,  1.0,
  
  // Right face
   1.0, -1.0, -1.0,
   1.0,  1.0, -1.0,
   1.0,  1.0,  1.0,
   1.0, -1.0,  1.0,
  
  // Left face
  -1.0, -1.0, -1.0,
  -1.0, -1.0,  1.0,
  -1.0,  1.0,  1.0,
  -1.0,  1.0, -1.0
};
float vCubeCol[4*24];

const float lerpValue[] = {0.0f};

GLuint shaderProgram;
GLuint vao;
GLuint CreateProgram(std::vector<GLuint> shaderList){
	auto prog = glCreateProgram();
	for(auto s:shaderList){
		glAttachShader(prog,s);
	}
	glLinkProgram(prog);
	GLint status;
	glGetProgramiv(prog,GL_LINK_STATUS,&status);
	if(status == GL_FALSE){
		GLint infoLogLength;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH,&infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength+1];
		glGetProgramInfoLog(prog,infoLogLength,NULL,strInfoLog);
		fprintf(stderr,"Linker Failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
	for(auto s:shaderList){
		glDetachShader(prog,s);
		glDeleteShader(s);
	}
	return prog;
}
void reshape(int w, int h){
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	return;
}
void InitProgram(){
	std::vector<GLuint> shaderList;
	shaderList.push_back(CreateShaderFromFile(GL_VERTEX_SHADER,"vShader.txt"));
	shaderList.push_back(CreateShaderFromFile(GL_FRAGMENT_SHADER,"fShader.txt"));
	shaderProgram = CreateProgram(shaderList);
	return;

}
void init(){
	glewExperimental = GL_TRUE;
	glewInit();	
	InitProgram();
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	
	for(int i=0;i<96;i+=4){
		vCubeCol[i] = rand()/float(RAND_MAX);
		vCubeCol[i+1] = rand()/float(RAND_MAX);
		vCubeCol[i+2] = rand()/float(RAND_MAX);
		vCubeCol[i+3] = 1.0;
	}
glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
}
template <typename T>
class buffer{
	protected:
		GLuint obj;
		GLenum target;
		int size;
		int elemSize;
		T* data;
	public:
		buffer(T* data, GLenum targ, int size, int elemSize)
			:target{targ},size{size},elemSize{elemSize}{
			glGenBuffers(1,&obj);
			size /= sizeof(T);	
			this->data = new T[size];
			std::cerr << size << std::endl;
			memcpy(this->data,data,size);

			update(data);
		}
		void update(T* data){
			glBindBuffer(target,obj);
			glBufferData(target,size,data,GL_STATIC_DRAW); //FOR NOW
			glBindBuffer(target,0);
		}
		void apply(){
			glBindBuffer(target,obj);
		}
		T* getData(){return data;}
		int getSize(){return size;}
		int getElemSize(){return elemSize;}
		GLuint getObj(){return obj;}
		~buffer(){
			delete[] data;
		}
};

 class attrib: public buffer<float>{
	 private:
	 GLuint loc;
	 public:
	 attrib(float* data, int size, int elemSize, int loc)
		 :buffer{data,GL_ARRAY_BUFFER,size,elemSize}{
		 this->loc = loc; //attrib location
	}
	void apply(){
		buffer::apply();
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc,elemSize,GL_FLOAT,GL_FALSE,0,0);
	 }

	 ~attrib(){
	 }
	
 };

class uniform{

//TO BE ADDED LATER.
};

class GlutManager{
	private:
	GLFWwindow* window;
	attrib* vPos;
	attrib* vCol;
	attrib* vLerp;
	attrib* vCubePos;
	attrib* vCubeCol;
	buffer<unsigned short>* bFace;
	public:

GlutManager(int argc, char** argv){
		glutInit(&argc,argv);
		
		int width = 500;
		int height = 500;

		if(!glfwInit()){
			fprintf(stderr,"ERROR: CANNOT INITIALIZE GLFW3\n");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

		window = glfwCreateWindow(width,height,"first",NULL,NULL);
		//glfwSetWindowSizeCallback(window,[](GLFWwindow* window, int w, int h){
		//		glViewport(0,0,w,h);
		//		});

		glfwMakeContextCurrent(window);
		init();
		vPos = new attrib((float*)vertexPositions,sizeof(vertexPositions),3,0);
		vCol = new attrib((float*)vertexColors, sizeof(vertexColors),4,1);
		vLerp = new attrib((float*)lerpValue,sizeof(lerpValue),1,2);

		vCubePos = new attrib((float*)::vCubePos,sizeof(::vCubePos),3,0);
		vCubeCol = new attrib((float*)::vCubeCol,96*sizeof(unsigned short),4,1);
		bFace = new buffer<unsigned short>((unsigned short*)vCubeFace,GL_ELEMENT_ARRAY_BUFFER,sizeof(vCubeFace),3);
//CURRENTLY EDITING HERE
}
	void run(){
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		static float prevTime = glutGet(GLUT_ELAPSED_TIME);
		static float timeFrame = 50.0f;

		do{
		glClearColor(0.0,0.0,0.0,1.0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);

		GLint numUniform;
		glGetProgramiv(shaderProgram,GL_ACTIVE_UNIFORMS,&numUniform);
		std::cout << numUniform << std::endl;

		vPos->apply();
		vCol->apply();
		vLerp->apply();
		vCubePos->apply();
		bFace->apply();
		vCubeCol->apply();

		float curTime = glutGet(GLUT_ELAPSED_TIME);
		glm::mat4 mMat;
		glm::mat4 pMat;
		pMat = glm::perspective(45.0f,1.0f,0.1f,100.0f);
		glm::mat4 vMat = glm::lookAt(glm::vec3(0.0f,0.0f,-5.0f),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
		//mMat = glm::translate(mMat, glm::vec3(0.5,0.5,0.0));
		mMat = glm::rotate(mMat,(curTime-prevTime)/timeFrame*glm::radians(180.0f),glm::vec3(0.50f,0.76f,0.29f));
		//mMat = glm::translate(mMat,glm::vec3(0.5,-0.5,0.0));

		mMat = glm::translate(mMat,glm::vec3(0,0,0));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"mMat"),1,GL_FALSE,glm::value_ptr(mMat));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"pMat"),1,GL_FALSE,glm::value_ptr(pMat));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"vMat"),1,GL_FALSE,glm::value_ptr(vMat));

		//glDrawArrays(GL_TRIANGLES,0,36);

		glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_SHORT,(GLvoid*)0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glUseProgram(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		}while(glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS
				&& glfwWindowShouldClose(window) == 0);
		std::cout << "LOOP OVER!" << std::endl;
	}
	~GlutManager()
	{
		delete vCol;
		delete vPos;
		delete vLerp;
		glfwDestroyWindow(window);
		glfwTerminate();	
	}


};

int main(int argc, char** argv){
	
	std::cout << "BEGIN!" <<std::endl;
	auto glut = GlutManager(argc,argv);
	std::cout << "RUN!" << std::endl;
	glut.run();
	std::cout << "END!" << std::endl;
	return 0;
}
