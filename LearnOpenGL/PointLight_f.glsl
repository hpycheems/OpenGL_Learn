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

struct PointLight{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform PointLight pointerLight;

uniform vec3 viewPos;

void main(){
	vec3 texColor = texture(material.diffuse, TexCoord).rgb;
	vec3 ambient = pointerLight.ambient * texColor;

	vec3 lightDir = normalize(pointerLight.position - FragPos);
	vec3 norm = normalize(Normal);
	float diff = max(0, dot(norm, lightDir));
	vec3 diffuse = pointerLight.diffuse * (diff * texColor);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfDir = normalize(viewDir + lightDir);
	float spec = pow(max(0, dot(norm, halfDir)), material.shininess);
	vec3 specular = pointerLight.specular * (spec * texture(material.specular, TexCoord).rgb);

	float dis = length(pointerLight.position - FragPos);
	float attenuation = 1.0 / (pointerLight.constant + pointerLight.linear * dis + pointerLight.quadratic * (dis * dis));
	vec3 result = (ambient + diffuse + specular) * attenuation;
	FragColor = vec4(result, 1);
}