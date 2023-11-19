#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


struct Material{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	float shininess;
};
uniform Material material;

struct DirectionLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirectionLight directionLight;

struct PointLight{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform PointLight pointLight;

uniform vec3 viewPos;

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);
	float diff = max(0, dot(normal, lightDir));
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(0, dot(normal, halfDir)), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	vec3 result = ambient + diffuse + specular;

	return result;
	return vec3(1);
}

vec3 CalcPointLihgt(PointLight light, vec3 normal, vec3 viewDir){
	
	float dir = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dir + light.quadratic * (dir * dir));

	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(0, dot(normal, lightDir));
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(0, dot(halfDir, normal)), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords)) * attenuation;
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords)) * attenuation;

	
	vec3 result = ambient + diffuse + specular;
	return result;
}

void main()
{    
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 finalColor = vec3(0);
	//finalColor = CalcDirectionLight(directionLight, norm, viewDir);
	finalColor += CalcPointLihgt(pointLight, norm, viewDir);

	FragColor = vec4(finalColor, 1);
}