#pragma once
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include<iostream>

//GL Includes
#include"../Dependencies/glm/glm.hpp"
#include"../Dependencies/glm/gtc/matrix_transform.hpp"
#include"Shader.h"
#include"Transform.h"

class PointLight
{
public:

	PointLight(const glm::vec3& position_, const glm::vec3& ambient_, const glm::vec3& diffuse_, const glm::vec3& specular_, float constant_ = 1.0f, float linear_ = 0.09f, float quadratic_ = 0.032f);
	PointLight(const glm::vec3& position_, const glm::vec3& ambient_, const glm::vec3& diffuse_, const glm::vec3& specular_, const glm::vec3& parameter = glm::vec3(1.0f, 0.09f, 0.032f));

	void setPosition(const glm::vec3& position_);
	void setPosition(float x, float y, float z);
	void setAmbient(const glm::vec3& ambient_);
	void setAmbient(float x, float y, float z);
	void setDiffuse(const glm::vec3& diffuse_);
	void setDiffuse(float x, float y, float z);
	void setSpecular(const glm::vec3& specular_);
	void setSpecular(float x, float y, float z);
	void setConstant(float constant_);
	void setLinear(float linear_);
	void setQuadratic(float quadratic_);

	void TransData(Shader& shader, int index);
private:
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

#endif