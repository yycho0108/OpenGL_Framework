#include "GLProgram.h"
#include "GLShader.h"
#include "GLObject.h"
#include "App.h"
#include </home/jamiecho/Downloads/glm/glm/glm.hpp>
#include "/home/jamiecho/Downloads/glm/glm/gtc/matrix_transform.hpp"
#include "/home/jamiecho/Downloads/glm/glm/gtc/type_ptr.hpp"

GLProgram* shaderProgram;
GLObject* Cube;

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

void init(){
	std::vector<GLuint> shaderList;
	auto v = GLShader(GL_VERTEX_SHADER, "vShader.txt");
	auto f = GLShader(GL_FRAGMENT_SHADER, "fShader.txt");

	shaderList.push_back(v);
	shaderList.push_back(f);
	shaderProgram = new GLProgram(shaderList);
	Cube = new GLObject();
	
	for(int i=0;i<96;i+=4){
		vCubeCol[i] = rand()/float(RAND_MAX);
		vCubeCol[i+1] = rand()/float(RAND_MAX);
		vCubeCol[i+2] = rand()/float(RAND_MAX);
		vCubeCol[i+3] = 1.0;
	}
	std::cout << "!!"<<sizeof(::vCubePos) << std::endl;
	auto vPos = new GLAttrib(::vCubePos,sizeof(::vCubePos),3,0);
	auto vCol = new GLAttrib(::vCubeCol,96*sizeof(float),4,1);
	auto vInd = new GLBuffer((void*)::vCubeFace,GL_ELEMENT_ARRAY_BUFFER,sizeof(vCubeFace),sizeof(*vCubeFace),3);
	GLBuffer vDummy((void*)"1,2,3,4,5",GL_ARRAY_BUFFER,sizeof("1,2,3,4,5"),sizeof('0'),1);
	Cube->push(*vPos);
	Cube->push(*vCol);
	Cube->push(*vInd);
	delete vPos;
	delete vCol;
	delete vInd;
	glEnable(GL_DEPTH_TEST);
}
float angle = 0;

void display(){
	glClearColor(1.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glUseProgram(*shaderProgram);

	/*GLint numUniform;
	GLint numAttrib;
	glGetProgramiv(*shaderProgram,GL_ACTIVE_UNIFORMS,&numUniform);	
	glGetProgramiv(*shaderProgram,GL_ACTIVE_ATTRIBUTES,&numAttrib);
	std::cout << numUniform << ',' << numAttrib <<std::endl;
	*/

	glm::mat4 mMat;
	mMat = glm::rotate(mMat,glm::radians(angle+=5),glm::vec3(0.50f,0.76f,0.29f));
	//mMat = glm::translate(mMat,glm::vec3(0,0,0));
	glm::mat4 pMat = glm::perspective(45.0f,1.0f,0.1f,100.0f);
	glm::mat4 vMat = glm::lookAt(glm::vec3(0.0f,0.0f,-5.0f),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
	//mMat = glm::translate(mMat, glm::vec3(0.5,0.5,0.0));
	//mMat = glm::translate(mMat,glm::vec3(0.5,-0.5,0.0));
	//char uName[20];
	glUniformMatrix4fv(glGetUniformLocation(*shaderProgram,"mMat"),1,GL_FALSE,glm::value_ptr(mMat));
	glUniformMatrix4fv(glGetUniformLocation(*shaderProgram,"pMat"),1,GL_FALSE,glm::value_ptr(pMat));
	glUniformMatrix4fv(glGetUniformLocation(*shaderProgram,"vMat"),1,GL_FALSE,glm::value_ptr(vMat));

	Cube->apply();
	Cube->draw();
}
int main(int argc, char** argv){
	App myApp(argc,argv);
	myApp.setInit(init);
	myApp.setDisplay(display);
	myApp.run();
	return 0;
}
