#include "chackError.h"
#include <assert.h>
#include <glad/glad.h>
#include <iostream>

void checkError()
{
	GLenum err = glGetError();
	switch (err)
	{
	case GL_NO_ERROR:
		return;
	case GL_INVALID_ENUM:
		std::cout << "GL_INVALID_ENUM" << std::endl;
		break;
	case GL_INVALID_VALUE:
		std::cout << "GL_INVALID_VALUE" << std::endl;
		break;
	case GL_INVALID_OPERATION:
		std::cout << "GL_INVALID_OPERATION" << std::endl;
		break;
	case GL_OUT_OF_MEMORY:
		std::cout << "GL_OUT_OF_MEMORY" << std::endl;
		break;
	default:
		break;
	}
	assert(false);
}