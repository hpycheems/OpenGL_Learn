#include "Light.h"

Light::Light(const char* vertexShader, const char* fragmentShader, glm::vec3 position): 
	lightPosition(position),light(vertexShader, fragmentShader)
{

}

void Light::setAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void Light::setDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec3 speculer)
{
	this->speculer = speculer;
}

void Light::use()
{
	light.use();
}

void Light::setMat4(const char* name, glm::mat4 parameter)
{
	light.setMat4(name, parameter);
}

void Light::setVec3(const char* name, glm::vec3 parameter)
{
	light.setVec3(name, parameter);
}
