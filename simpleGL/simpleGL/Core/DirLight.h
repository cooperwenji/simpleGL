#pragma once
#ifndef DIRLIGHT_H
#define DIRLIGHT_H

#include<iostream>

//GL Includes
#include"../Dependencies/glm/glm.hpp"
#include"../Dependencies/glm/gtc/matrix_transform.hpp"
#include"Shader.h"

class DirLight
{
public:
	DirLight(const glm::vec3& direction_, const glm::vec3& ambient_, const glm::vec3& diffuse_, const glm::vec3& specular_)
		:direction(direction_), ambient(ambient_), diffuse(diffuse_), specular(specular_)
	{

	}
	
	void TransData(Shader& shader)
	{
		shader.setVec3("dirLight.direction", direction);
		shader.setVec3("dirLight.ambient", ambient);
		shader.setVec3("dirLight.diffuse", diffuse);
		shader.setVec3("dirLight.specular", specular);
	}

private:
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

#endif