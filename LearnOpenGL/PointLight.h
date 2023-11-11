#pragma once
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class PointLight
{
public:
	PointLight(const char* vertexShader, const char* fragmentShader, glm::vec3 position);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 speculer);
	void use();
	void setMat4(const char* name, glm::mat4 parameter);
	void setVec3(const char* name, glm::vec3 parameter);
	void setFloat(const char* name, float parameter);

	float constant;
	float linear;
	float quadratic;

	Shader object;

	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

