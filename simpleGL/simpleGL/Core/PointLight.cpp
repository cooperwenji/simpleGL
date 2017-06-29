#include"PointLight.h"

PointLight::PointLight(const glm::vec3& position_, const glm::vec3& ambient_, const glm::vec3& diffuse_, const glm::vec3& specular_, float constant_, float linear_, float quadratic_)
	:position(position_),constant(constant_),linear(linear_),quadratic(quadratic_),ambient(ambient_),diffuse(diffuse_),specular(specular_)
{

}

PointLight::PointLight( const glm::vec3& position_, const glm::vec3& ambient_, const glm::vec3& diffuse_, const glm::vec3& specular_, const glm::vec3& parameter)
	:position(position_),constant(parameter.x),linear(parameter.y),quadratic(parameter.z), ambient(ambient_), diffuse(diffuse_), specular(specular_)
{

}

void PointLight::setPosition(const glm::vec3& position_)
{
	this->position = position_;
}

void  PointLight::setPosition(float x, float y, float z)
{
	this->position = glm::vec3(x, y, z);
}

void PointLight::setAmbient(const glm::vec3& ambient_)
{
	this->ambient = ambient_;
}

void PointLight::setAmbient(float x, float y, float z)
{
	this->ambient = glm::vec3(x, y, z);
}

void PointLight::setDiffuse(const glm::vec3& diffuse_)
{
	this->diffuse = diffuse_;
}

void PointLight::setDiffuse(float x, float y, float z)
{
	this->diffuse = glm::vec3(x, y, z);
}

void PointLight::setSpecular(const glm::vec3& specular_)
{
	this->specular = specular_;
}

void PointLight::setSpecular(float x, float y, float z)
{
	this->specular = glm::vec3(x, y, z);
}

void PointLight::setConstant(float constant_)
{
	this->constant = constant_;
}

void PointLight::setLinear(float linear_)
{
	this->linear = linear_;
}

void PointLight::setQuadratic(float quadratic_)
{
	this->quadratic = quadratic_;
}

void PointLight::TransData(Shader& shader, int index)
{
	std::string index_str = "";
	Transform::int2str(index, index_str);

	shader.setVec3("pointLights[" + index_str +"].position", this->position);
	shader.setVec3("pointLights[" + index_str + "].ambient", this->ambient);
	shader.setVec3("pointLights[" + index_str + "].diffuse", this->diffuse);
	shader.setVec3("pointLights[" + index_str + "].specular", this->specular);
	shader.setFloat("pointLights[" + index_str + "].constant", this->constant);
	shader.setFloat("pointLights[" + index_str + "].linear_para", this->linear);
	shader.setFloat("pointLights[" + index_str + "].quadratic", this->quadratic);
}