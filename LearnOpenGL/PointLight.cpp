#include "PointLight.h"

PointLight::PointLight(const char* vertexShader, const char* fragmentShader, glm::vec3 position):object(vertexShader, fragmentShader)
{
	this->position = position;
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
	this->ambient = glm::vec3(0.2f);
	this->diffuse = glm::vec3(0.5f);
	this->specular = glm::vec3(1.0f);
}

void PointLight::setAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void PointLight::setDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void PointLight::setSpecular(glm::vec3 speculer)
{
	this->specular = specular;
}

void PointLight::use()
{
	object.use();
}

void PointLight::setMat4(const char* name, glm::mat4 parameter)
{
	object.setMat4(name, parameter);
}

void PointLight::setVec3(const char* name, glm::vec3 parameter)
{
	object.setVec3(name, parameter);
}

void PointLight::setFloat(const char* name, float parameter)
{
	object.setFloat(name, parameter);
}
