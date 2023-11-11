#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SpotLight
{
public:
	SpotLight(glm::vec3 position, glm::vec3 direction, float cutoff, float outcutoff);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 speculer);

	float constant;
	float linear;
	float quadratic;

	glm::vec3 position;
	glm::vec3 direction;
	float cutoff;
	float outcutoff;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

