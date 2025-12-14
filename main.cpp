#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "wrapper/chackError.h"
#include "application/Application.h"

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
	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
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
	prepare();
	prepareSingleBuffer();
	prepareInterleavedBuffer();
	//执行窗口循环
	while (Application::getInstance()->update())
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	//4.释放资源
	Application::getInstance()->destroy();

    return 0;
}