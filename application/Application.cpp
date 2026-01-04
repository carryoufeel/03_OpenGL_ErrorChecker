#include "Application.h"
#include "Application.h"
#include "Application.h"
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

Application* Application::mInstance = nullptr;

Application::~Application()
{
}

Application* Application::getInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new Application();
	}
	return mInstance;
}

bool Application::init(const int& width, const int& height)
{
	mWidth = width;
	mHeight = height;
	//1.初始化GLFW
	glfwInit();
	//设置OpenGL版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//设置OpenGL配置
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//2.创建窗口
	mWindow = glfwCreateWindow(mWidth, mHeight, "openGLstudy", NULL, NULL);
	if(mWindow==nullptr)
	{
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	//加载OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize GLAD" << std::endl;
		return false;
	}

	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	glfwSetKeyCallback(mWindow, key_callback);

	glfwSetMouseButtonCallback(mWindow, mouse_callback);

	glfwSetCursorPosCallback(mWindow, cursor_callback);

	glfwSetWindowUserPointer(mWindow,this);

	return true;
}


bool Application::update()
{
	//检查窗口是否关闭
	if (glfwWindowShouldClose(mWindow))
	{
		return false;
	}
	//处理事件
	glfwPollEvents();
	//交换缓冲区
	glfwSwapBuffers(mWindow);
	return true;
}

bool Application::destroy()
{
	glfwTerminate();
	return true;
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//if(Application::getInstance()->mResizeCallBack!=nullptr)
	//Application::getInstance()->mResizeCallBack(width,height);
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app->mResizeCallBack != nullptr)
		app->mResizeCallBack(width, height);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app->mKeyCallBack != nullptr)
		app->mKeyCallBack(key, scancode, action, mods);
}

void Application::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app->mMouseCallBack != nullptr)
		app->mMouseCallBack(button, action, mods);
}

void Application::cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app->mCursorCallBack != nullptr)
		app->mCursorCallBack(xpos, ypos);
}

Application::Application()
{
}

