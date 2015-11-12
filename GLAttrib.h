#ifndef _GLATTRIB
#define _GLATTRIB
#include "GLBuffer.h"

class GLAttrib:
	public GLBuffer{
		private:
			GLuint loc;
		public:
			GLAttrib(float* data, int size, int elemSize, int loc);
			void apply();
			~GLAttrib();
};
#endif
