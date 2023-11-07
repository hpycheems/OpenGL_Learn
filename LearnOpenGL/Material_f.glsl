#version 330 core 
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 speculer;
	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

void main(){
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = 0.5 * dot(norm,lightDir) + 0.5;
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = normalize(reflect(-lightDir, norm));
	float spec = pow(max(dot(reflectDir, viewDir),0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.speculer);

	vec3 result = (ambient + diffuse + specular);
	FragColor = vec4(result, 1);
}