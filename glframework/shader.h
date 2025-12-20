#pragma once

#include "core.h"
#include <string>

class Shader
{
public:
	Shader(const char * vertexPath,const char * fragmentPath);
	~Shader();

	void begin();
	void end();
	void setFloat(const std::string &name,float value);

private:
	void checkCompileErrors(GLuint target, std::string type);

private:
	GLuint mProgram{ 0 };
};