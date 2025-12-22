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
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, const float* value);

	void setInt(const std::string& name, int value);

private:
	void checkCompileErrors(GLuint target, std::string type);

private:
	GLuint mProgram{ 0 };
};