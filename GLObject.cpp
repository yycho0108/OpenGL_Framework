#include "GLObject.h"
std::list<glm::mat4> absMat;
GLint GLObject::mMatLoc = -1;


GLObject::GLObject():angle{0.0f}{
		glGenVertexArrays(1,&vao);
}

	void GLObject::push(const GLAttrib& attrib){
		Attribs.push_back(attrib);
	}	
	void GLObject::push(const GLBuffer& buffer){
		Buffers.push_back(buffer);
	}
	void GLObject::push(std::shared_ptr<GLObject>& child){
		push(child.get());
	}
	void GLObject::push(GLObject* child){
		Children.push_back(child);
	}
	void GLObject::setPos(glm::vec3 newPos){
		std::swap(this->Position,newPos);
	}
	void GLObject::offsetPos(const glm::vec3& offset){
		Position += offset;
	}
	void GLObject::setAxis(glm::vec3 newAxis){
		std::swap(this->RotAxis,newAxis);
	}
	void GLObject::offsetAxis(const glm::vec3& offset){
		RotAxis += offset;
	}
	void GLObject::setAngle(GLfloat angle){
		//std::swap(this->angle,angle);
		this->angle = angle;
	}
	void GLObject::offsetAngle(const GLfloat& angle){
		this->angle += angle;
	}
	glm::vec3 GLObject::getPos(){return Position;}
	glm::vec3 GLObject::getAxis(){return RotAxis;}
	GLfloat GLObject::getAngle(){return angle;}
	void GLObject::apply(){	
		new(&this->mMat) glm::mat4();
		mMat = glm::rotate_slow(mMat,angle,RotAxis);
		mMat = glm::translate(mMat,Position);
		
		glBindVertexArray(vao);
		for(auto& a:Attribs){
			a.apply();
		}
		for(auto& b:Buffers){
			b.apply();
		}
	}
	void GLObject::draw(const glm::mat4& absMat){	
		auto myMat = absMat *this->mMat;
		glUniformMatrix4fv(mMatLoc,1,GL_FALSE,glm::value_ptr(myMat));
		
		glDrawElements(GL_TRIANGLES,Buffers[0].getSize(),GL_UNSIGNED_SHORT,0);
		//TENTATIVE
		
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
		for (auto c : Children){
			c->apply();
			c->draw(myMat);
		}

		//glDrawArrays(GL_TRIANGLES,0,3);
	}
void GLObject::relocate(GLuint shaderProgram){
	mMatLoc = glGetUniformLocation(shaderProgram,"mMat");
}
GLObject::~GLObject(){};
