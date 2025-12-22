#include <iostream>

#include "glframework/core.h"
#include "glframework/shader.h"

#include "wrapper/chackError.h"
#include "application/Application.h"

#define STB_IMAGE_IMPLEMENTATION
#include "application/stb_image.h"

#pragma comment(lib, "opengl32.lib")

GLuint vao, program;
GLuint texture;
Shader* shader = nullptr;
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
		 -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f
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

	shader->setFloat("time", (float)glfwGetTime());
	shader->setFloat("speed", 4.0f);

	//shader->setVector3("uColor", 0.3f, 0.4f, 0.5f);
	//float color[3] = { 0.9f,0.2f,0.2f };
	//shader->setVector3("uColor", color);
	shader->setInt("sampler", 0);
	//绑定VAO
	GL_CALL(glBindVertexArray(vao));
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	GL_CALL(glBindVertexArray(0));
	shader->end();
}

void prepareTexture()
{
	//1 使用stb_image加载图片
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true); //翻转图片y轴
	unsigned char* data = stbi_load("./assets/textures/boki.png", &width, &height, &channels, STBI_rgb_alpha);
	//2 生成纹理对象并激活单元绑定
	GL_CALL(glGenTextures(1, &texture));
	GL_CALL(glActiveTexture(GL_TEXTURE0));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
	//3 传输纹理数据
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	//释放数据
	stbi_image_free(data);
	//4 设置纹理过滤方式
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//5 设置纹理环绕方式
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));//U
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));//V


}

int main()
{
	if (!Application::getInstance()->init())
	{
		return -1;
	}
	Application::getInstance()->setResizeCallBack(OnResize);
	Application::getInstance()->setKeyCallBack(onKey);
	
	//设置清屏颜色
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	prepareShader();
	//prepare();
	//prepareSingleBuffer();
	//prepareInterleavedBuffer();
	prepareVAO();
	prepareTexture();
	//执行窗口循环
	while (Application::getInstance()->update())
	{
		render();
	}

	//4.释放资源
	Application::getInstance()->destroy();

    return 0;
}