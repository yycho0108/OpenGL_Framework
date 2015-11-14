#ifndef _GLOBJECT
#define _GLOBJECT
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
#include "GLBuffer.h"
#include "GLAttrib.h"
#include "GLUniform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLObject{
	private:
		GLuint vao;
		GLint mMatLoc;
		std::vector<GLAttrib> Attribs;
		std::vector<GLBuffer> Buffers;//namely, vertex Indices
		GLUniform<glm::mat4> mMat;
		glm::vec3 Position;
		glm::vec3 RotAxis;
		GLfloat angle;
	public:	
		GLObject();
		void setPos(glm::vec3 newPos);
		void offsetPos(const glm::vec3& offset);
		void setAxis(glm::vec3 newAxis);
		void offsetAxis(const glm::vec3& offset);
		void setAngle(GLfloat angle);
		void offsetAngle(const GLfloat& angle);
		glm::vec3 getPos();
		glm::vec3 getAxis();
		GLfloat getAngle();
		void push(const GLAttrib& attrib);
		void push(const GLBuffer& buffer);
		void apply();
		void draw();
		void relocate(GLuint shaderProgram);
		//update
		~GLObject();
		//VAO
		//
};

#endif
