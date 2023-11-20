#version 330 core 
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main(){
	
	vec4 texcolor = texture(texture1, TexCoords);
	if(texcolor.a < 0.1){
		discard;
	}
	
	FragColor = texcolor;
}