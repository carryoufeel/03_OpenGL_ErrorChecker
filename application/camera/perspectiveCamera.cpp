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