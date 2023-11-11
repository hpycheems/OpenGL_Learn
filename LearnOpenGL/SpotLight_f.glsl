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

void main(){
	
	vec3 texColor = texture(material.diffuse, TexCoord).rgb;
	vec3 ambient = spotLight.ambient * texColor;
	vec3 lightDir = normalize(spotLight.position - FragPos);
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = normalize(reflect(-lightDir, norm));

	vec3 result = vec3(0);

	float theta = dot(lightDir, normalize(-spotLight.direction));
	float epsilon = spotLight.cutoff - spotLight.outcutoff;
	float intensity = clamp((theta - spotLight.outcutoff) / epsilon, 0.0, 1.0);

	float diff = max(0, dot(norm, lightDir));
	vec3 diffuse = spotLight.diffuse * (diff * texColor);
	float spec = pow(max(0, dot(viewDir, reflectDir)), material.shininess);
	vec3 specular = spotLight.specular * (spec * texture(material.specular, TexCoord).rgb);

	diffuse *= intensity;
	specular *= intensity;

	float dic = length(spotLight.position - FragPos);
	float attenuation = 1.0 / (spotLight.constant + spotLight.linear * dic + spotLight.quadratic * (dic * dic));
	result = (ambient + diffuse + specular) * attenuation;

	FragColor = vec4(result, 1);	
}