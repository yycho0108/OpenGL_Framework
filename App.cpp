#include "App.h"
char *_dummy[1] = {(char*)""};
char** dummy = (char**)_dummy;

App::App(int argc, char** argv){
	glutInit(&argc,argv);
	if(!glfwInit()){
		std::cerr << "ERROR: CANNOT INSTANTIATE GLFW3" << std::endl;
	}
	int width = 500, height = 500;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	window = glfwCreateWindow(width,height,"first",NULL,NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
}

void App::run(){
	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
	startTime = glutGet(GLUT_ELAPSED_TIME);
	init();
	do{
		display();
		glUseProgram(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0);
}
//reshape
//etc..
App::~App(){
	glfwDestroyWindow(window);
	glfwTerminate();
}
