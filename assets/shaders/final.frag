#version 440 core

in vec3 color;
in vec3 worldPos;
in vec3 normal;

out vec4 outColor;

uniform vec3 lightPos;

void main(){
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - worldPos);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1, 1, 1);

	float ambStr = 0.1f;
	vec3 ambient = ambStr * vec3(1, 1, 1);

	vec3 result = (diffuse) * color;

	outColor = vec4(result, 1);
}