#version 330 core 
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;


void main(){
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	//float diff = max(dot(norm, lightDir), 0);
	float diff = (0.5 * dot(norm, lightDir)) + 0.5;
	vec3 diffuse = lightColor * diff ;

	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 finalColor = (ambient + diffuse + specular) * objectColor; 

	FragColor = vec4(finalColor, 1.0f);
}