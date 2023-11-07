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

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main(){
	
	vec3 texColor = texture(material.diffuse, TexCoord).rgb;
	vec3 ambient = light.ambient * texColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = 0.5 * dot(lightDir, norm) + 0.5f;
	vec3 diffuse = light.diffuse * (diff * texColor);

	vec3 specColor = texture(material.specular, TexCoord).rgb;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = normalize( reflect(-lightDir, norm));
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	vec3 specular = light.specular * (spec * specColor);

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1);
}