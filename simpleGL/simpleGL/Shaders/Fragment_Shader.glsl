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
uniform Material material;  //����Ĳ�������

uniform DirLight dirLight;  //ƽ�й�
uniform PointLight pointLights[NR_POINT_LIGHTS]; //���Դ
uniform SpotLight spotLight; //�۹��

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 texColor);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 texColor );
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 texColor);

void main()
{
	//һЩ����
	vec3 norm = normalize(fs_in.Normal);
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);

	vec4 texColor = texture(material.texture_diffuse1, fs_in.TexCoords);

	//��һ��������ƽ�й���
	vec4 result = CalcDirLight(dirLight, norm, viewDir, texColor);

	//�ڶ���������ƹ���
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, fs_in.FragPos, viewDir, texColor);

	//������������۹��
	result += CalcSpotLight(spotLight, norm, fs_in.FragPos, viewDir, texColor);

	FragColor = result;
	
}


vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 texColor)
{
	vec3 lightDir = normalize(-light.direction);
	//����������ǿ��
	float diff = max(dot(normal, lightDir), 0.0);
	//���㾵�淴��ǿ��
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//�ϲ��������շ���
	vec4 ambient = vec4(light.ambient, 1.0f)  * texColor;
	vec4 diffuse = vec4(light.diffuse, 1.0f)   * diff * texColor;
	vec4 specular = vec4(light.specular, 1.0f) * spec  * texColor;

	return (ambient + diffuse + specular);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 texColor)
{
	vec3 lightDir = normalize(light.position - fragPos);
	//����������ǿ��
	float diff = max(dot(normal, lightDir), 0.0);
	//���㾵�淴��ǿ��
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//����˥��ǿ��
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear_para * distance + light.quadratic * distance * distance);

	//�ϲ��������շ���
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

	//����������ǿ��
	float diff = max(dot(normal, lightDir), 0.0);
	//���㾵�淴��ǿ��
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		
    //�ϲ��������շ���
	vec4 ambient = intensity * vec4(light.ambient, 1.0f) * texColor;
	vec4 diffuse = intensity * vec4(light.diffuse, 1.0f) * diff * texColor;
	vec4 specular = intensity * vec4(light.specular, 1.0f) * spec * texColor;

	return (ambient + diffuse + specular);

}

