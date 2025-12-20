#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "wrapper/chackError.h"
#include "application/Application.h"
#pragma comment(lib, "opengl32.lib")
GLuint vao, program;

void onKey(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W)
	{

	}

	std::cout << "key:" << key << "action:" << action<<"mods:"<< mods<<std::endl;
}

void OnResize(int width,int height)
{
	std::cout << "OnResize new size" << width << "," << height << std::endl;
	GL_CALL(glViewport(0, 0, width, height));
}

void prepareVBO()
{
	//1 创建VBO,没分配显存
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));
	std::cout << "vbo id:" << vbo << std::endl;
	//2 销毁VBO
	GL_CALL(glDeleteBuffers(1, &vbo));
	//3 创建N个VBO
	GLuint vbos[3] = { 0 };
	GL_CALL(glGenBuffers(3, vbos));
	for (int i = 0; i < 3; ++i)
	{
		std::cout << "vbos[" << i << "] id:" << vbos[i] << std::endl;
	}
	//4 销毁N个VBO
	GL_CALL(glDeleteBuffers(3, vbos));
}

void prepare()
{
	float vertices[] = {
		// 位置              
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	//准备VBO
	int vbo = 0;
	GL_CALL(glGenBuffers(1, (GLuint*)&vbo));  //创建VBO
	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	//传输数据，分配显存
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
}

void prepareSingleBuffer()
{
	float positions[] = {
		// 位置              
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	float colors[] = {
		// 颜色
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	//准备VBO
	GLuint posVbo = 0, colorVbo = 0;
	GL_CALL(glGenBuffers(1, &posVbo));  //创建位置VBO
	GL_CALL(glGenBuffers(1, &colorVbo));  //创建颜色VBO
	//准备VAO
	GLuint vao = 0;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));

	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
	//描述位置属性
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	//描述颜色属性
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	//解绑VAO
	GL_CALL(glBindVertexArray(0));

}

void prepareVAO()
{
	float vertexData[] = {
		// 位置              // 颜色
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f
		- 1.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f

	};
	unsigned int indices[] = {
		0, 1, 2, // first triangle
		2, 1, 3  // second triangle

	};
	//准备VBO
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));  //创建位置VBO
	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));
	//准备EBO
	GLuint ebo = 0;
	GL_CALL(glGenBuffers(1, &ebo));  //创建EBO
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	//准备VAO
	vao = 0;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));
	//描述位置属性
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	//描述颜色属性
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	//绑定EBO到VAO
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));


	//解绑VAO
	GL_CALL(glBindVertexArray(0));
}

void prepareInterleavedBuffer()
{
	float vertexData[] = {
		// 位置              // 颜色
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	//准备VBO
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));  //创建位置VBO
	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));
	//准备VAO
	vao = 0;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));
	//描述位置属性
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	//描述颜色属性
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	//解绑VAO
	GL_CALL(glBindVertexArray(0));
}

void prepareShader()
{
	//编译顶点着色器	
	const char* vertexShaderSource = R"(
		#version 460 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;
		out vec3 ourColor;
		void main()
		{
			gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
			ourColor = aColor;
		}
	)";
	//编译片段着色器
	const char* fragmentShaderSource = R"(
		#version 460 core
		out vec4 FragColor;
		in vec3 ourColor;
		void main()
		{
			//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			FragColor = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f);
		}
	)";
	//创建Shader Program
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	
	//为程序输入代码
	GL_CALL(glShaderSource(vertex, 1, &vertexShaderSource, NULL));
	GL_CALL(glShaderSource(fragment, 1, &fragmentShaderSource, NULL));

	//执行编译
	int success=0;
	char infoLog[512];
	GL_CALL(glCompileShader(vertex));
	//检查编译错误
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	GL_CALL(glCompileShader(fragment));
	//检查编译错误
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//创建程序
	program = glCreateProgram();

	//添加着色器到程序
	GL_CALL(glAttachShader(program, vertex));
	GL_CALL(glAttachShader(program, fragment));

	//链接程序
	
	glLinkProgram(program);
	//检查链接错误
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//清理着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void render()
{
	//清理
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	//使用着色器程序
	GL_CALL(glUseProgram(program));
	//绑定VAO
	GL_CALL(glBindVertexArray(vao));
	//绘制
	//glDrawArrays(GL_TRIANGLES, 0, 4);
	//strip
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//fan
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//lines
	//glDrawArrays(GL_LINES, 0, 4);
	//line strip
	//glDrawArrays(GL_LINE_STRIP, 0, 4);
	//EBO
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	GL_CALL(glBindVertexArray(0));
}

int main()
{
	if (!Application::getInstance()->init())
	{
		return -1;
	}
	Application::getInstance()->setResizeCallBack(OnResize);
	Application::getInstance()->setKeyCallBack(onKey);
	
	//设置清屏颜色
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	prepareShader();
	//prepare();
	//prepareSingleBuffer();
	//prepareInterleavedBuffer();
	prepareVAO();
	//执行窗口循环
	while (Application::getInstance()->update())
	{
		render();
	}

	//4.释放资源
	Application::getInstance()->destroy();

    return 0;
}