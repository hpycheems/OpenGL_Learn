#version 330 core 
out vec4 FragColor;

in vec2 TexCoords;


uniform sampler2D colorTexture;

const float offset = 1.0 / 300.0;

void main(){
	//·´Ïà
	//FragColor =	 vec4(vec3(1 - texture(colorTexture, TexCoords)), 1.0);

	//»Ò¶È
	//FragColor = texture(colorTexture, TexCoords);
	//float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
	//FragColor = vec4(vec3(average), 1);

	//Èñ»¯ Ä£ºý
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0, offset),
		vec2(offset, offset),
		vec2(-offset, 0),
		vec2(0, 0),
		vec2(offset, 0),
		vec2(-offset, -offset),
		vec2(0, -offset),
		vec2(offset, -offset)
	);

	//Èñ»¯ºË
	float kernel[9] = float[](
		-1, -1, -1,
		-1, 9,  -1,
		-1, -1, -1
	);
	//Ä£ºýºË
	float kernelVague[9] = float[](
		 1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16  
	);
	//±ßÔµ¼ì²âºË
	float kernelEdge[9] = float[](
		1, 1, 1,
		1, -8,1,
		1, 1, 1
	);

	vec3 sampleTex[9];
	for(int i = 0; i < 9; ++i){
		sampleTex[i] = vec3(texture(colorTexture, TexCoords.st + offsets[i]));
	}

	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; ++i){
		col += sampleTex[i] * kernelEdge[i];
	}
	FragColor = vec4(col, 1);
}