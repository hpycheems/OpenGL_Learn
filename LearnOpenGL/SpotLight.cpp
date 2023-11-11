#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float cutoff, float outcutoff)
{
	this->position = position;
	this->direction = direction;
	this->cutoff = cutoff;

	this->constant = 1.0f;
	this->linear = 0.02f;
	this->quadratic = 0.032f;

	this->ambient = glm::vec3(0.2f);
	this->diffuse = glm::vec3(0.5f);
	this->specular = glm::vec3(1.0f);
}

void SpotLight::setAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void SpotLight::setDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void SpotLight::setSpecular(glm::vec3 speculer)
{
	this->specular = specular;
}
