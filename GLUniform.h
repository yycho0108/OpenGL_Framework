#ifndef _GLUNIFORM
#define _GLUNIFORM
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
//vec3
//vec4
//mat4
//float
//uint
//bool
//int
template <typename T>
class GLUniform{
	private:
		GLint loc;
		T val;
	public:
		GLint getLoc(){return loc;};
		GLUniform(GLint loc, T val):loc{loc}{
			std::swap(this->val,val);
		}
		GLUniform():loc{-1}{
		}
		void update(T val){
			std::swap(this->val,val);
		}
		T& get(){return val;}
		void apply(T& val);
		void apply();
		void setLoc(GLint loc){this->loc=loc;}
};
#endif
