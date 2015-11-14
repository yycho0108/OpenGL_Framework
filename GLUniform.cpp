#include "GLUniform.h"

template<>
void GLUniform<GLint>::apply(GLint& val){
	glUniform1i(getLoc(),val);
}

template<>
void GLUniform<GLfloat>::apply(GLfloat& val){
	glUniform1f(getLoc(),val);
}

template<>
void GLUniform<glm::vec2>::apply(glm::vec2& val){
	glUniform2fv(getLoc(),1,glm::value_ptr(val));
}

template<>
void GLUniform<glm::vec3>::apply(glm::vec3& val){
	glUniform3fv(getLoc(),1,glm::value_ptr(val));
}

template<>
void GLUniform<glm::vec4>::apply(glm::vec4& val){
	glUniform4fv(getLoc(),1,glm::value_ptr(val));
}

template<>
void GLUniform<glm::mat4>::apply(glm::mat4& val){
	glUniformMatrix4fv(getLoc(),1,GL_FALSE,glm::value_ptr(val));
}

template<typename T>
void GLUniform<T>::apply(){
	apply(this->val);
}

template class GLUniform<GLint>;
template class GLUniform<GLfloat>;
template class GLUniform<glm::vec2>;
template class GLUniform<glm::vec3>;
template class GLUniform<glm::vec4>;
template class GLUniform<glm::mat4>;
