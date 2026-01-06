#include "perspectiveCamera.h"
#include "perspectiveCamera.h"
PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
	:Camera(), mFov(fov), mAspectRatio(aspectRatio), mNear(near), mFar(far)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

glm::mat4 PerspectiveCamera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(mFov), mAspectRatio, mNear, mFar);
}

void PerspectiveCamera::scale(float deltaScale)
{
	auto front = glm::cross(mUp,mRight);
	mPosition += (front * deltaScale);
}
