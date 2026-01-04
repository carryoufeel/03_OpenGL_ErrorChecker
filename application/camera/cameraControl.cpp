#include "cameraControl.h"

CameraControl::CameraControl()
{
}

CameraControl::~CameraControl()
{
}

void CameraControl::onMouse(int button, int action, double xpos, double ypos)
{
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
}

void CameraControl::onKey(int key, int action, int mods)
{
	if (action == GLFW_REPEAT)
	{
		return;
	}
	bool pressed = action == GLFW_PRESS ? true : false;
	mKeyMap[key] = pressed;
}

void CameraControl::update()
{

}
