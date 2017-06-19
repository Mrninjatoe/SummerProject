#version 440 core

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec3 vertColor;
layout(location = 3) in vec2 vertUV;

out vec3 color;

uniform float nice;

void main(){
	gl_Position = vec4(vertPos / gl_InstanceID, 1);
	color = vec3(vertColor.x * sin(nice), vertColor.y, vertColor.z);
}