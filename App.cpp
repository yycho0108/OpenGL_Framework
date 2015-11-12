#include "App.h"

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
	std::cout << "QUITTING FROM APP?" << std::endl;
}
void App::setInit(std::function<void()> init){
this->init = init;
}
void App::setDisplay(std::function<void()> display){
	this->display = display;
}
//reshape
//etc..
App::~App(){
	glfwDestroyWindow(window);
	glfwTerminate();
}
