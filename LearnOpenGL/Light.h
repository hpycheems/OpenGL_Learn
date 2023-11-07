#pragma once
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light(const char* vertexShader, const char* fragmentShader ,glm::vec3 position = glm::vec3(1.2f, 1.0f, 1.2f));
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 speculer);
	void use();
	void setMat4(const char* name, glm::mat4 parameter);
	void setVec3(const char* name, glm::vec3 parameter);

	Shader light;
	glm::vec3 lightPosition;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 speculer;
};

