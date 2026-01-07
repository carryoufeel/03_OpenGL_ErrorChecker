#include "geometry.h"
#include <vector>

Geometry::Geometry()
{

}

Geometry::~Geometry()
{
	if (mVao != 0)
	{
		glDeleteVertexArrays(1, &mVao);
	}
	if (mPosVbo != 0)
	{
		glDeleteBuffers(1, &mPosVbo);
	}
	if (mColorVbo != 0)
	{
		glDeleteBuffers(1, &mColorVbo);
	}
	if (mEbo != 0)
	{
		glDeleteBuffers(1, &mEbo);
	}
	if (mNormalVbo != 0)
	{
		glDeleteBuffers(1, &mNormalVbo);
	}
}

Geometry* Geometry::createBox(float size)
{
	Geometry* geometry = new Geometry();
	geometry->mIndicesCount = 36;
	float halfSize = size * 0.5f;
	float positions[] = {
		// front face
		-halfSize, -halfSize,  halfSize,  // 0
		 halfSize, -halfSize,  halfSize,  // 1
		 halfSize,  halfSize,  halfSize,  // 2
		-halfSize,  halfSize,  halfSize,  // 3

		// back face
		-halfSize, -halfSize, -halfSize,  // 4
		-halfSize,  halfSize, -halfSize,  // 5
		 halfSize,  halfSize, -halfSize,  // 6
		 halfSize, -halfSize, -halfSize,  // 7

		 // top face
		 -halfSize, halfSize,  halfSize,   // 8
		  halfSize, halfSize,  halfSize,   // 9
		  halfSize, halfSize, -halfSize,   // 10
		 -halfSize, halfSize, -halfSize,   // 11

		 // bottom face
		 -halfSize, -halfSize, -halfSize,  // 12
		  halfSize, -halfSize, -halfSize,  // 13
		  halfSize, -halfSize,  halfSize,  // 14
		 -halfSize, -halfSize,  halfSize,  // 15

		 // right face
		  halfSize, -halfSize,  halfSize,  // 16
		  halfSize, -halfSize, -halfSize,  // 17
		  halfSize,  halfSize, -halfSize,  // 18
		  halfSize,  halfSize,  halfSize,  // 19

		  // left face
		  -halfSize, -halfSize, -halfSize,  // 20
		  -halfSize, -halfSize,  halfSize,  // 21
		  -halfSize,  halfSize,  halfSize,  // 22
		  -halfSize,  halfSize, -halfSize   // 23
	};
	float uvs[] = {
		0.0,0.0,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
		0.0,0.0,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
		0.0,0.0,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
		0.0,0.0,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
		0.0,0.0,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
		0.0,0.0,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
	};
	float normals[] = {
		0.0f, 0.0f, 1.0f,  // Front face
		0.0f,0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f,0.0f, 1.0f,
		0.0f, 0.0f, -1.0f, // Back face
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f,  // Top face
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, // Bottom face
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  // Right face
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,  // Left face
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f
	};

	unsigned int indices[] = {
		0,1,2, 2,3,0,       //front face
		4,5,6, 6,7,4,       //back face
		8,9,10, 10,11,8,    //top face
		12,13,14, 14,15,12,  //bottom face
		16,17,18, 18,19,16,  //right face
		20,21,22, 22,23,20   //left face
	};
	GLuint& posVbo = geometry->mPosVbo;
	GLuint& uvVbo = geometry->mUvVbo;
	GLuint& normalVbo = geometry->mNormalVbo;

	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBindVertexArray(0);

	return geometry;
}

Geometry* Geometry::createSphere(float radius)
{
	Geometry* geometry = new Geometry();
	//位置，uv，索引
	std::vector<GLfloat> positions;
	std::vector<GLfloat> uvs;
	std::vector<GLfloat> normals;
	std::vector<GLuint> indices;
	int numLatLines = 60;//纬线
	int numLongLines = 60;//经线
	
	for (int i = 0; i <= numLatLines; ++i)
	{
		for (int j = 0; j <= numLongLines; ++j)
		{
			float phi = i*glm::pi<float>() / numLatLines;
			float theta = j * 2.0f * glm::pi<float>() / numLongLines;
			float y = radius*cos(phi);
			float x = radius * sin(phi) * cos(theta);
			float z = radius * sin(phi) * sin(theta);
			float u = 1 - (float)j / numLongLines;
			float v = 1 - (float)i / numLatLines;
			positions.push_back(x);
			positions.push_back(y);
			positions.push_back(z);
			uvs.push_back(u);
			uvs.push_back(v);

			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		}
	}
	for (int i = 0; i < numLatLines; ++i)
	{
		for (int j = 0; j < numLongLines; ++j)
		{
			int first = (i * (numLongLines + 1)) + j;
			int second = first + numLongLines + 1;
			int third = first + 1;
			int fourth = second + 1;
			indices.push_back(first);
			indices.push_back(second);
			indices.push_back(third);

			indices.push_back(third);
			indices.push_back(second);
			indices.push_back(fourth);
		}
	}
	GLuint& posVbo = geometry->mPosVbo;
	GLuint& uvVbo = geometry->mUvVbo;
	GLuint& normalVbo = geometry->mNormalVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(float), uvs.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBindVertexArray(0);

	geometry->mIndicesCount = static_cast<uint32_t>(indices.size());
	return geometry;
}

Geometry* Geometry::createPlane(float width, float heigth)
{
	Geometry* geometry = new Geometry();
	geometry->mIndicesCount = 6;
	float halfWidth = width * 0.5f;
	float halfHeigth = heigth * 0.5f;
	float positions[] = {
		-halfWidth, -halfHeigth, 0.0f,  // 0
		 halfWidth, -halfHeigth, 0.0f,  // 1
		 halfWidth,  halfHeigth, 0.0f,  // 2
		-halfWidth,  halfHeigth, 0.0f   // 3
	};
	float uvs[] = {
		0.0,0.0,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
	};

	float normals[] = {
		0.0f, 0.0f, 1.0f,  // Front face
		0.0f,0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f,0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0,1,2, 2,3,0        //plane
	};
	GLuint& posVbo = geometry->mPosVbo;
	GLuint& uvVbo = geometry->mUvVbo;
	GLuint& normalVbo = geometry->mNormalVbo;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBindVertexArray(0);

	return geometry;
}
