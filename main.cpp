#include <iostream>

#include "glframework/core.h"
#include "glframework/shader.h"

#include "wrapper/chackError.h"
#include "application/Application.h"

#include "glframework/texture.h"

#pragma comment(lib, "opengl32.lib")

GLuint vao;
Shader* shader = nullptr;
Texture* grassTexture = nullptr;
Texture* landTexture = nullptr;
Texture* noiseTexture = nullptr;
glm::mat4 transform(1.0f);
glm::mat4 viewMatrix(1.0f);
glm::mat4 orthoMatrix(1.0f);
glm::mat4 perspectiveMatrix(1.0f);

void onKey(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W)
	{

	}

	std::cout << "key:" << key << "action:" << action<<"mods:"<< mods<<std::endl;
}

void OnResize(int width,int height)
{
	std::cout << "OnResize new size" << width << "," << height << std::endl;
	GL_CALL(glViewport(0, 0, width, height));
}

void OnMouse(int button, int action, int mods)
{
	std::cout << "OnMouse button:" << button << " action:" << action << " mods:" << mods << std::endl;
}

void OnCursor(double xpos, double ypos)
{
	std::cout << "OnCursor xpos:" << xpos << " ypos:" << ypos << std::endl;
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
	//transform = translation * rotation ;
	transform = rotation * translation;
}

void doRotation() 
{
	static float angle = 0.0f;
	angle += 1.0f;
	transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
}

void prepareVBO()
{
	//1 创建VBO,没分配显存
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));
	std::cout << "vbo id:" << vbo << std::endl;
	//2 销毁VBO
	GL_CALL(glDeleteBuffers(1, &vbo));
	//3 创建N个VBO
	GLuint vbos[3] = { 0 };
	GL_CALL(glGenBuffers(3, vbos));
	for (int i = 0; i < 3; ++i)
	{
		std::cout << "vbos[" << i << "] id:" << vbos[i] << std::endl;
	}
	//4 销毁N个VBO
	GL_CALL(glDeleteBuffers(3, vbos));
}

void prepare()
{
	float vertices[] = {
		// 位置              
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	//准备VBO
	int vbo = 0;
	GL_CALL(glGenBuffers(1, (GLuint*)&vbo));  //创建VBO
	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	//传输数据，分配显存
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
}

void prepareSingleBuffer()
{
	float positions[] = {
		// 位置              
		 -0.5f,  0.5f, 0.0f,
		 -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f
	};
	float colors[] = {
		// 颜色
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	//准备VBO
	GLuint posVbo = 0, colorVbo = 0;
	GL_CALL(glGenBuffers(1, &posVbo));  //创建位置VBO
	GL_CALL(glGenBuffers(1, &colorVbo));  //创建颜色VBO
	//准备VAO
	GLuint vao = 0;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));

	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
	//描述位置属性
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	//描述颜色属性
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	//解绑VAO
	GL_CALL(glBindVertexArray(0));

}

void prepareVAO()
{
	float vertexData[] = {
		// 位置              // 颜色
		 -0.8f,  0.8f, 0.1f, 1.0f, 0.0f, 0.0f,
		 -0.8f, -0.8f, 0.1f, 0.0f, 1.0f, 0.0f,
		0.8f, -0.8f, 0.1f, 0.0f, 0.0f, 1.0f,
		0.8f,  0.8f, 0.1f, 1.0f, 1.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 2, // first triangle
		0, 2, 3  // second triangle

	};
	float uvs[]= {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	//准备VBO
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));  //创建位置VBO
	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));

	GLuint uvVbo = 0;
	GL_CALL(glGenBuffers(1, &uvVbo));  //创建UV VBO
	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));

	//准备EBO
	GLuint ebo = 0;
	GL_CALL(glGenBuffers(1, &ebo));  //创建EBO
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	//准备VAO
	vao = 0;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));
	//描述位置属性
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	//描述颜色属性
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	//加入UV属性描述数据
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
	GL_CALL(glEnableVertexAttribArray(2));
	GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));

	//绑定EBO到VAO
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

	//解绑VAO
	GL_CALL(glBindVertexArray(0));
}

void prepareInterleavedBuffer()
{
	float vertexData[] = {
		// 位置              // 颜色
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	//准备VBO
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));  //创建位置VBO
	//绑定VBO
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));
	//准备VAO
	vao = 0;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));
	//描述位置属性
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	//描述颜色属性
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
	//解绑VAO
	GL_CALL(glBindVertexArray(0));
}

void prepareShader()
{
	shader = new Shader("./assets/shaders/vertex.glsl", "./assets/shaders/fragment.glsl");
}

void render()
{
	//清理
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	//使用着色器程序
	shader->begin();

	//shader->setFloat("time", (float)glfwGetTime());
	//shader->setFloat("speed", 4.0f);

	//shader->setVector3("uColor", 0.3f, 0.4f, 0.5f);
	//float color[3] = { 0.9f,0.2f,0.2f };
	//shader->setVector3("uColor", color);
	shader->setInt("grassSampler",0);
	shader->setMatrix4x4("transform", transform);
	shader->setMatrix4x4("viewMatrix", viewMatrix);
	shader->setMatrix4x4("projectionMatrix", perspectiveMatrix);
	//shader->setInt("landSampler",1);
	//shader->setInt("noiseSampler",2);
	//绑定VAO
	GL_CALL(glBindVertexArray(vao));
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	GL_CALL(glBindVertexArray(0));
	shader->end();
}

void prepareTexture()
{
	grassTexture = new Texture("./assets/textures/hjs.jpg", 0);
	//landTexture = new Texture("./assets/textures/land.jpg", 1);
	//noiseTexture = new Texture("./assets/textures/noise.png", 2);
}

void prepareCamera()
{
	//eye:相机位置
	//center:观察目标点
	//up:穹顶向量
	viewMatrix = glm::lookAt(glm::vec3(0.5f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void prepareOrtho()
{
	//float aspect = (float)Application::getInstance()->getWidth() / (float)Application::getInstance()->getHeight();
	orthoMatrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f);
}

void preparePerspective()
{
	//fovy:y轴视野角度
	//aspect:宽高比
	//near:近裁剪面
	//far:远裁剪面
	perspectiveMatrix = glm::perspective(glm::radians(90.0f),(float)Application::getInstance()->getWidth() / (float)Application::getInstance()->getHeight(), 0.1f, 100.0f);
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
	//设置清屏颜色
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	prepareShader();
	//prepare();
	//prepareSingleBuffer();
	//prepareInterleavedBuffer();
	prepareVAO();
	prepareTexture();
	prepareCamera();
	//prepareOrtho();
	preparePerspective();
	//doRotationTransform();
	//doTranslationTransform();
	//doScaleTransform();
	//doTransform();
	//执行窗口循环
	while (Application::getInstance()->update())
	{
		//doRotation();
		render();
	}
	delete grassTexture;
	delete landTexture;
	delete shader;
	//4.释放资源
	Application::getInstance()->destroy();

    return 0;
}