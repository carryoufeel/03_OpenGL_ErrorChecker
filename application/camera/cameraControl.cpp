#include "cameraControl.h"
#include "cameraControl.h"
#include <iostream>

CameraControl::CameraControl()
{

}

CameraControl::~CameraControl()
{

}

void CameraControl::onMouse(int button, int action, double xpos, double ypos)
{
	std::cout << "onMouse button:" << button << " action:" << action << " xpos:" << xpos << " ypos:" << ypos << std::endl;
	bool pressed = action == GLFW_PRESS?true:false;
	if (pressed)
	{
		mCurrentX = (float)xpos;
		mCurrentY = (float)ypos;
	}
	switch (button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
		mLeftMouseDown = pressed;
		break;
		case GLFW_MOUSE_BUTTON_RIGHT:
		mRightMouseDown = pressed;
		break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
		mMiddleMouseDown = pressed;
		break;
	default:
		break;
	}
}

void CameraControl::onCursor(double xpos, double ypos)
{
	std::cout << "onCursor xpos:" << xpos << " ypos:" << ypos << std::endl;
}

void CameraControl::onKey(int key, int action, int mods)
{
	std::cout << "onKey key:" << key << " action:" << action << " mods:" << mods << std::endl;
	if (action == GLFW_REPEAT)
	{
		return;
	}
	bool pressed = action == GLFW_PRESS ? true : false;
	mKeyMap[key] = pressed;
}

void CameraControl::onScroll(float offset)
{

}

void CameraControl::update()
{

}
