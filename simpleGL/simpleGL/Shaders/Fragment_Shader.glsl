#version 330 core

struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear_para;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float innerCutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 4

in VS_OUT
{
	vec2 TexCoords;
	vec3 Normal;
	vec3 FragPos;
}fs_in;



out vec4 FragColor;

//uniform sampler2D texture_diffuse1;

uniform vec3 viewPos;
uniform Material material;  //物体的材质属性

uniform DirLight dirLight;  //平行光
uniform PointLight pointLights[NR_POINT_LIGHTS]; //点光源
uniform SpotLight spotLight; //聚光灯

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 texColor);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 texColor );
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 texColor);

void main()
{
	//一些属性
	vec3 norm = normalize(fs_in.Normal);
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);

	vec4 texColor = texture(material.texture_diffuse1, fs_in.TexCoords);

	//第一步，计算平行光照
	vec4 result = CalcDirLight(dirLight, norm, viewDir, texColor);

	//第二步，计算灯光照
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, fs_in.FragPos, viewDir, texColor);

	//第三步，计算聚光灯
	result += CalcSpotLight(spotLight, norm, fs_in.FragPos, viewDir, texColor);

	FragColor = result;
	
}


vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 texColor)
{
	vec3 lightDir = normalize(-light.direction);
	//计算漫反射强度
	float diff = max(dot(normal, lightDir), 0.0);
	//计算镜面反射强度
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//合并各个光照分量
	vec4 ambient = vec4(light.ambient, 1.0f)  * texColor;
	vec4 diffuse = vec4(light.diffuse, 1.0f)   * diff * texColor;
	vec4 specular = vec4(light.specular, 1.0f) * spec  * texColor;

	return (ambient + diffuse + specular);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 texColor)
{
	vec3 lightDir = normalize(light.position - fragPos);
	//计算漫反射强度
	float diff = max(dot(normal, lightDir), 0.0);
	//计算镜面反射强度
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//计算衰减强度
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear_para * distance + light.quadratic * distance * distance);

	//合并各个光照分量
	vec4 ambient = vec4(light.ambient, 1.0f) * texColor;
	vec4 diffuse = vec4(light.diffuse, 1.0f)  * diff * texColor;
	vec4 specular = vec4(light.specular , 1.0f) * spec * texColor;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 texColor)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	//计算漫反射强度
	float diff = max(dot(normal, lightDir), 0.0);
	//计算镜面反射强度
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		
    //合并各个光照分量
	vec4 ambient = intensity * vec4(light.ambient, 1.0f) * texColor;
	vec4 diffuse = intensity * vec4(light.diffuse, 1.0f) * diff * texColor;
	vec4 specular = intensity * vec4(light.specular, 1.0f) * spec * texColor;

	return (ambient + diffuse + specular);

}

