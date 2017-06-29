#include"SpotLight.h"

SpotLight::SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float innerCutOff_, float outerCutOff_, const glm::vec3& ambient_, const glm::vec3& diffuse_, const glm::vec3& specular_)
	:position(position_), direction(direction_), innerCutOff(innerCutOff_), outerCutOff(outerCutOff_),ambient(ambient_), diffuse(diffuse_), specular(specular_)
{

}

void SpotLight::TransData(Shader& shader)
{
	shader.setVec3("spotLight.position", this->position);
	shader.setVec3("spotLight.direction", this->direction);
	shader.setFloat("spotLight.innerCutOff", this->innerCutOff);
	shader.setFloat("spotLight.outerCutOff", this->outerCutOff);
	shader.setVec3("spotLight.ambient", this->ambient);
	shader.setVec3("spotLight.diffuse", this->diffuse);
	shader.setVec3("spotLight.specular", this->specular);
}