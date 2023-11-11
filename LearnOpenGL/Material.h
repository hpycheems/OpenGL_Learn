#pragma once
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public :
	Material(const char* vertexShader, const char* fragmentShader);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setShininess(float shininess);
	void use();
	void setTexture(unsigned int diffuse);
	void setTexture(unsigned int diffuse, unsigned int specular);
	void setInt(const char* name, unsigned int texture);
	void setMat4(const char* name, glm::mat4 parameter);
	void setVec3(const char* name, glm::vec3 parameter);
	void setFloat(const char* name, float parameter);

	Shader object;
	unsigned int diffuseID;
	unsigned int specularID;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

