#include <cstdint>

#pragma once

class GLFWwindow;

using ResizeCallBack = void(*)(int ,int);

using KeyCallBack = void(*)(int, int, int, int);

using MouseCallBack = void(*)(int, int, int);

using CursorCallBack = void(*)(double, double);

class Application
{
public:
	~Application();
	static Application* getInstance();

	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }

	//1.init
	bool init(const int& width=1920,const int& height=1080);
	//2.update
	bool update();
	//3,destroy
	bool destroy();

	void setResizeCallBack(ResizeCallBack callback) { mResizeCallBack = callback; }

	void setKeyCallBack(KeyCallBack callback) { mKeyCallBack = callback; }

	void setMouseCallBack(MouseCallBack callback) { mMouseCallBack = callback; }

	void setCursorCallBack(CursorCallBack callback) { mCursorCallBack = callback; }

private:
	//c++类内函数指针
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window,int button,int action,int mods);
	static void cursor_callback(GLFWwindow* window, double xpos, double ypos);
	static Application* mInstance;
	Application();

	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };
	ResizeCallBack mResizeCallBack{ nullptr };
	KeyCallBack mKeyCallBack{ nullptr };
	MouseCallBack mMouseCallBack{ nullptr };
	CursorCallBack mCursorCallBack{ nullptr };

};
