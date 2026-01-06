#include "trackBallCameraControl.h"

TrackBallCameraControl::TrackBallCameraControl()
{
}

TrackBallCameraControl::~TrackBallCameraControl()
{
}

void TrackBallCameraControl::onCursor(double xpos, double ypos)
{
	if (mLeftMouseDown)
	{
		float delatX = (xpos - mCurrentX)*mSensitivity;
		float delatY = (ypos - mCurrentY)*mSensitivity;
		pitch(-delatY);
		yaw(-delatX);
	}
	else if (mMiddleMouseDown)
	{
		float delatX = (xpos - mCurrentX) * mMoveSpeed;
		float delatY = (ypos - mCurrentY) * mMoveSpeed;
		mCamera->mPosition += mCamera->mUp * delatY;
		mCamera->mPosition -= mCamera->mRight * delatX;

	}
	mCurrentX = (float)xpos;
	mCurrentY = (float)ypos;
}

void TrackBallCameraControl::onScroll(float offset)
{
	mCamera->scale(offset*mScaleSpeed);
}

void TrackBallCameraControl::pitch(float angle)
{
	auto mat = glm::rotate(glm::mat4(1.0f),glm::radians(angle),mCamera->mRight);
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}

void TrackBallCameraControl::yaw(float angle)
{
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}
