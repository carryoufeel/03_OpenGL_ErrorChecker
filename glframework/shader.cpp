#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "shader.h"

#include "../wrapper/chackError.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	//读取着色器代码
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) 
	{
		throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}
	//创建Shader Program
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	//为程序输入代码
	GL_CALL(glShaderSource(vertex, 1, &vShaderCode, NULL));
	GL_CALL(glShaderSource(fragment, 1, &fShaderCode, NULL));
	//执行编译
	GL_CALL(glCompileShader(vertex));
	checkCompileErrors(vertex, "COMPLE");
	GL_CALL(glCompileShader(fragment));
	checkCompileErrors(fragment, "COMPLE");
	//创建程序
	mProgram = glCreateProgram();

	//添加着色器到程序
	GL_CALL(glAttachShader(mProgram, vertex));
	GL_CALL(glAttachShader(mProgram, fragment));

	//链接程序

	glLinkProgram(mProgram);
	checkCompileErrors(mProgram,"LINK");
	//清理着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{

}


void Shader::setFloat(const std::string& name, float value)
{
	GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
	GL_CALL(glUniform1f(location, value));
}

void Shader::setVector3(const std::string& name, float x, float y, float z)
{
	GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
	GL_CALL(glUniform3f(location, x, y, z));
}

void Shader::setVector3(const std::string& name, const float* value)
{
	GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
	
	GL_CALL(glUniform3fv(location, 1, value));
}

void Shader::setInt(const std::string& name, int value)
{
	GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
	GL_CALL(glUniform1i(location, value));
}

void Shader::checkCompileErrors(GLuint target, std::string type)
{
	int success = 0;
	char infoLog[1024];
	if (type == "COMPLE")
	{
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(target, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	else if(type=="LINK")
	{
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(target, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}
	else
	{
		std::cout << "ERROR::SHADER::UNKNOWN_TYPE" << std::endl;
	}
}

void Shader::begin()
{
	GL_CALL(glUseProgram(mProgram));
}

void Shader::end()
{
	GL_CALL(glUseProgram(0));
}

