#include "DirectionLight.h"

DirectionLight::DirectionLight(const char* vertexShader, const char* fragmentShader, glm::vec3 direction) 
	: _direction(direction),
	ambient(glm::vec3(0.2f)), 
	diffuse(glm::vec3(0.5f)), 
	specular(glm::vec3(1.0f)), 
	_directionLight(vertexShader, fragmentShader)
{
	
}

void DirectionLight::setAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void DirectionLight::setDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void DirectionLight::setSpecular(glm::vec3 speculer)
{
	this->specular = specular;
}

void DirectionLight::use()
{
	_directionLight.use();
}

void DirectionLight::setMat4(const char* name, glm::mat4 parameter)
{
	_directionLight.setMat4(name, parameter);
}

void DirectionLight::setVec3(const char* name, glm::vec3 parameter)
{
	_directionLight.setVec3(name, parameter);
}
