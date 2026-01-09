#pragma once
#include "core.h"

class Object {
public:
	Object();
	~Object();

	void setPosiotion(glm::vec3 pos);
	
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void setScale(glm::vec3 scale);
	
	glm::mat4 getModelMatrix();

protected:
	glm::vec3 mPosition{ 0.0f };
	float mAngleX{ 0.0f };
	float mAngleY{ 0.0f };
	float mAngleZ{ 0.0f };

	glm::vec3 mScale{ 1.0f };
};
