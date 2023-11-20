#version 330 core
out vec4 FragColo;

in vec2 TexCoords;

uniform sampler2D glassTexture;

void main(){
	FragColo = texture(glassTexture, TexCoords);
}