#pragma once

#include "../../glframework/core.h"
#include "camera.h"
#include <map>

class CameraControl
{
public:
	CameraControl();
	~CameraControl();

	virtual void onMouse(int button, int action ,double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onKey(int key, int action, int mods);
	virtual void onScroll(float offset);

	virtual void update();

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float sensitivity) { mSensitivity = sensitivity; }
	void setScaleSpeed(float s) { mScaleSpeed = s; }

protected:
	bool mLeftMouseDown=false;
	bool mRightMouseDown = false;
	bool mMiddleMouseDown = false;

	float mCurrentX = 0.0f;
	float mCurrentY = 0.0f;

	float mSensitivity = 0.2f;

	std::map<int, bool> mKeyMap;

	Camera* mCamera = nullptr;

	float mScaleSpeed = 0.2f;
};
