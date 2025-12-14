#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "wrapper/chackError.h"

void frameBufferSizeCallBack(GLFWwindow *window,int width,int height) 
{
	std::cout << "new size" << width << "," << height << std::endl;
	glViewport(0, 0, width, height);
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W)
	{

	}

	std::cout << "key:" << key << "action:" << action<<"mods:"<< mods<<std::endl;
}

int main()
{
	//1.初始化GLFW
	glfwInit();
	//设置OpenGL版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
	//设置OpenGL配置
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//2.创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "openGLstudy", NULL, NULL);
	glfwMakeContextCurrent(window);
	//注册回调函数
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);

	glfwSetKeyCallback(window,keyCallBack);
	//加载OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize GLAD" << std::endl;
		return -1;
	}
	//设置视口
	glViewport(0, 0, 800, 600);
	//设置清屏颜色
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//3.执行窗口循环
	while (!glfwWindowShouldClose(window))
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
		//glClear(-1);
		checkError();
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	//4.释放资源
	glfwTerminate();

    return 0;
}