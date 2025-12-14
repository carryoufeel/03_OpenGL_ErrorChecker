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

	//执行窗口循环
	while (Application::getInstance()->update())
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	//4.释放资源
	Application::getInstance()->destroy();

    return 0;
}