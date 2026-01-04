#include "camera.h"
#include "camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	glm::vec3 front = glm::cross(mUp, mRight);
	return glm::lookAt(
		mPosition,
		mPosition + front,
		mUp
	);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::identity<glm::mat4>();
}

void Camera::scale(float deltaScale)
{
}
