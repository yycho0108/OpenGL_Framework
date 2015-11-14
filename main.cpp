#include "GLProgram.h"
#include "GLShader.h"
#include "GLObject.h"
#include "App.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::shared_ptr<GLProgram> shaderProgram;
std::shared_ptr<GLObject> Cube;
std::shared_ptr<GLObject> Cube_2;
//GLObject* Cube;

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
class myApp:public App{
	private:
		bool depthClampEnabled=false;
	public:
	myApp():App(){};
	//myApp(int argc, char** argv):App(argc,argv){};
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

		//mMat = glm::translate(mMat,glm::vec3(0,0,0));
		glm::mat4 pMat = glm::perspective(45.0f,1.0f,0.1f,100.0f);
		glm::mat4 vMat = glm::lookAt(glm::vec3(0.0f,20.0f,-1.0f),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
		glUniformMatrix4fv(glGetUniformLocation(*shaderProgram,"pMat"),1,GL_FALSE,glm::value_ptr(pMat));
		glUniformMatrix4fv(glGetUniformLocation(*shaderProgram,"vMat"),1,GL_FALSE,glm::value_ptr(vMat));
		Cube->setAxis(glm::vec3(0.0f,0.0f,1.0f));
		Cube->offsetAngle(1.0f);
		//Cube->offsetPos(glm::vec3(0.01f,0.0f,0.0f));
		Cube_2->setAxis(glm::vec3(0.0f,1.0f,0.0f));
		Cube_2->offsetAngle(-5.0f);
		
		Cube->draw();
		//Cube_2->draw();
		//Cube_2->apply();
		//Cube_2->draw(glm::mat4());

	}
	
	void init(){
		std::vector<GLuint> shaderList;
		auto v = GLShader(GL_VERTEX_SHADER, "vShader.txt");
		auto f = GLShader(GL_FRAGMENT_SHADER, "fShader.txt");

		shaderList.push_back(v);
		shaderList.push_back(f);
		shaderProgram.reset(new GLProgram(shaderList));
		
		Cube.reset(new GLObject());
		Cube->relocate(*shaderProgram);
		Cube_2.reset(new GLObject());
		Cube_2->relocate(*shaderProgram);
		for(int i=0;i<96;i+=4){
			vCubeCol[i] = rand()/float(RAND_MAX);
			vCubeCol[i+1] = rand()/float(RAND_MAX);
			vCubeCol[i+2] = rand()/float(RAND_MAX);
			vCubeCol[i+3] = rand()/float(RAND_MAX);//i.0;
		}
		auto vPos = new GLAttrib(::vCubePos,sizeof(::vCubePos),3,0);
		auto vCol = new GLAttrib(::vCubeCol,96*sizeof(float),4,1);
		auto vInd = new GLBuffer((void*)::vCubeFace,GL_ELEMENT_ARRAY_BUFFER,sizeof(vCubeFace),sizeof(*vCubeFace),3);
		Cube->push(*vPos);
		Cube->push(*vCol);
		Cube->push(*vInd);
		Cube_2->push(*vPos);
		Cube_2->push(*vCol);
		Cube_2->push(*vInd);
		delete vPos;
		delete vCol;
		delete vInd;
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CW);
		Cube->setPos(glm::vec3(1.0f,1.0f,0.0f));
		Cube_2->setPos(glm::vec3(0.0f,0.0f,5.0f));
		Cube->push(Cube_2);
	};
};
void mouseEvent(GLFWwindow* window, double xPos, double yPos){
	// do nothing
}
void keyboardEvent(GLFWwindow* window, int key, int scanCode, int action, int mods){
	static bool depthClampEnabled = false;
	if(action == GLFW_PRESS){
			switch(key){
				case GLFW_KEY_SPACE:
					depthClampEnabled = !depthClampEnabled;
					depthClampEnabled?glEnable(GL_DEPTH_CLAMP):glDisable(GL_DEPTH_CLAMP);
					break;
				}
	}
}


int main(){
	myApp my_App;
	//myApp my_App(argc,argv);
	my_App.setKey(keyboardEvent);
	my_App.setMouse(mouseEvent);
	my_App.init();
	my_App.run();
	return 0;
}
