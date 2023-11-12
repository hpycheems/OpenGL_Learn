#version 330 core 
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
	sampler2D diffuse;
	sampler2D specular;
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

struct SpotLight{
	vec3 position;
	vec3 direction;

	float cutoff;
	float outcutoff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform SpotLight spotLight;

uniform vec3 viewPos;

vec3 CalcDirLihgt(DirectionLight light, vec3 normal, vec3 viewDir){
	
	vec3 lightDir = normalize(-light.direction);
	float diff = max(0, dot(normal, lightDir));
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(0, dot(normal, halfDir)), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	vec3 result = ambient + diffuse + specular;

	return result;
}

vec3 CalcPointLihgt(PointLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(0, dot(normal, lightDir));
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(0, dot(halfDir, normal)), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	float dir = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dir + light.quadratic * (dir * dir));
	vec3 result = ambient + (diffuse + specular) * attenuation;
	return result;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 halfDir = normalize(viewDir + lightDir);

	vec3 result;
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutoff - light.outcutoff;
	float intensity = clamp((theta - light.outcutoff) / epsilon, 0.0, 1.0);

	float diff = max(0, dot(lightDir, normal));
	float spec = pow(max(0, dot(halfDir, normal)), material.shininess);
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	float dir = length(FragPos - light.position);
	float attenuation = 1.0 / (light.constant + light.linear * dir + light.quadratic * (dir * dir));

	result = ambient + (diffuse + specular) * attenuation;
	return result;
}

void main(){
	vec3 finalColor = vec3(0);

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	finalColor += CalcDirLihgt(directionLight, norm, viewDir);
	finalColor += CalcPointLihgt(pointLight, norm, viewDir);
	finalColor += CalcSpotLight(spotLight, norm, viewDir);

	FragColor = vec4(finalColor, 1);	
}