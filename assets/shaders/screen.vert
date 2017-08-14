#version 440 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec3 vertColor;
layout(location = 3) in vec2 vertUV;

out vec2 texCoords;

void main(){
	texCoords = vertUV;
	gl_Position = vec4(vertPos.x * 2.0f, vertPos.y * 2.0f, 0.0f, 1);
}