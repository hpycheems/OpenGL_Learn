#include "Material.h"

Material::Material(const char* vertexShader, const char* fragmentShader) : object(vertexShader, fragmentShader)
{

}

void Material::setAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void Material::setDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void Material::setSpecular(glm::vec3 specular)
{
	this->specular = specular;
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}

void Material::use()
{
	object.use();
}

void Material::setTexture(unsigned int diffuse)
{
	this->diffuseID	 = diffuse;
}

void Material::setTexture(unsigned int diffuse, unsigned int specular)
{
	this->diffuseID = diffuse;
	this->specularID = specular;
}

void Material::setInt(const char* name, unsigned int texture)
{
	object.setInt(name, texture);
}

void Material::setMat4(const char* name, glm::mat4 parameter)
{
	object.setMat4(name, parameter);
}

void Material::setVec3(const char* name, glm::vec3 parameter)
{
	object.setVec3(name, parameter);
}

void Material::setFloat(const char* name, float parameter)
{
	object.setFloat(name, parameter);
}
