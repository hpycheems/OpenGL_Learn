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

uniform vec3 viewPos;

void main(){
	
	vec3 texColor = texture(material.diffuse, TexCoord).rgb;
	vec3 ambient = directionLight.ambient * texColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-directionLight.direction);
	float diff = max(0, dot(norm, lightDir));
	vec3 diffuse = directionLight.diffuse * (diff * texColor);

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = normalize(reflect(-lightDir, norm));
	float spec = pow(max(0, dot(viewDir, reflectDir)), material.shininess);
	vec3 specular = directionLight.specular * (spec * texture(material.specular, TexCoord).rgb);

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1);	
}