#include <iostream>

#include "glframework/core.h"
#include "glframework/shader.h"

#include "wrapper/chackError.h"
#include "application/Application.h"
#include "glframework/texture.h"
#pragma comment(lib, "opengl32.lib")

#include "application/camera/perspectiveCamera.h"
#include "application/camera/trackBallCameraControl.h"
#include "application/camera/gameCameraControl.h"

#include "glframework/geometry.h"

glm::vec3 lightDirection(-1.0f, -1.0f, -1.0f);
glm::vec3 lightColor(0.9f, 0.85f, 0.75f);

Geometry* geometry = nullptr;
Shader* shader = nullptr;

Texture* texture = nullptr;

glm::mat4 transform(1.0f);

PerspectiveCamera* camera = nullptr;
TrackBallCameraControl* cameraControl = nullptr;
 
void onKey(int key, int scancode, int action, int mods)
{
	cameraControl->onKey(key,action,mods);
}

void OnResize(int width,int height)
{
	GL_CALL(glViewport(0, 0, width, height));
}

void OnMouse(int button, int action, int mods)
{
	double xpos, ypos;
	Application::getInstance()->getCursorPosition(&xpos, &ypos);
	cameraControl->onMouse(button, action, xpos, ypos);
}

void OnCursor(double xpos, double ypos)
{
	cameraControl->onCursor(xpos, ypos);
}

void OnScroll(double offset)
{
	cameraControl->onScroll(offset);
}

void doRotationTransform()
{
	transform = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
}

void doTranslationTransform()
{
	transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f));
}

void doScaleTransform()
{
	transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
}

void doTransform()
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
	transform = rotation * translation;
}

void doRotation() 
{
	static float angle = 0.0f;
	angle += 1.0f;
	transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
}

void prepareVAO()
{
	//geometry = Geometry::createPlane(3.0f,2.0f);
	//geometry = Geometry::createSphere(1.0f);
	geometry = Geometry::createBox(1.0f);
}

void prepareShader()
{
	shader = new Shader("./assets/shaders/vertex.glsl", "./assets/shaders/fragment.glsl");
}

void render()
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
	shader->begin();

	shader->setInt("Sampler",0);
	shader->setMatrix4x4("modelMatrix", transform);
	shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
	shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());
	
	shader->setVector3("lightDirection", lightDirection);
	shader->setVector3("lightColor", lightColor);

	shader->setVector3("cameraPosition",camera->mPosition);

	GL_CALL(glBindVertexArray(geometry->getVao()));
	glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);
	GL_CALL(glBindVertexArray(0));
	shader->end();
}

void prepareTexture()
{
	texture = new Texture("./assets/textures/land.jpg", 0);
}

void prepareCamera()
{
	camera = new PerspectiveCamera(60.0f, 
		(float)Application::getInstance()->getWidth() / (float)Application::getInstance()->getHeight(), 
		0.1f, 1000.0f);
	cameraControl = new TrackBallCameraControl();
	cameraControl->setCamera(camera);
}

void prepareState()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

int main()
{
	if (!Application::getInstance()->init())
	{
		return -1;
	}
	Application::getInstance()->setResizeCallBack(OnResize);
	Application::getInstance()->setKeyCallBack(onKey);
	Application::getInstance()->setMouseCallBack(OnMouse);
	Application::getInstance()->setCursorCallBack(OnCursor);
	Application::getInstance()->setScrollCallback(OnScroll);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	prepareShader();
	prepareVAO();
	prepareTexture();
	prepareCamera();
	prepareState();
	//执行窗口循环
	while (Application::getInstance()->update())
	{
		cameraControl->update();
		render();
	}
	delete texture;
	delete shader;
	//4.释放资源
	Application::getInstance()->destroy();
    return 0;
}