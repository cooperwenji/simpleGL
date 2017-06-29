#pragma once
#ifndef  SPOTLIGHT_H
#define SPOTLIGHT_H

#include<iostream>
//GL Includes
#include"../Dependencies/glm/glm.hpp"
#include"../Dependencies/glm/gtc/matrix_transform.hpp"
#include"Shader.h"

class SpotLight
{
public:
	SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float innerCutOff_, float outerCutOff_, const glm::vec3& ambient_, const glm::vec3& diffuse_, const glm::vec3& specular_);
	void TransData(Shader& shader);

private:
	glm::vec3 position;
	glm::vec3 direction;
	float innerCutOff;
	float outerCutOff;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};


#endif // ! SPOTLIGHT_H


