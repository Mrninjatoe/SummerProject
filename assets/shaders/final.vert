#version 440 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec3 vertColor;
layout(location = 3) in vec2 vertUV;

out vec3 color;
out vec3 worldPos;
out vec3 normal;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main(){
	color = vertColor;
	worldPos = vec3(model * vec4(vertPos, 1)).xyz;
	normal = vec3(model * vec4(vertNormal, 1)).xyz;
	gl_Position = proj * view * model * vec4(vertPos, 1);
}