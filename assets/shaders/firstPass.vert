#version 440 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec3 vertColor;
layout(location = 3) in vec2 vertUV;

out vec3 color;
out vec3 worldPos;
out vec3 normal;
out vec2 uv;
out vec2 textureCoords1;
out vec2 textureCoords2;
out float blend;

uniform vec2 texOffset1;
uniform vec2 texOffset2;
uniform vec2 texCoordInfo;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main(){
	color = vertColor;
	uv = vertPos.xy + vec2(0.5, 0.5);
	uv.y = 1.0 - vertUV.y;
	uv /= texCoordInfo.x;
	textureCoords1 = uv + texOffset1;
	textureCoords2 = uv + texOffset2;
	blend = texCoordInfo.y;

	worldPos = vec3(model * vec4(vertPos, 1)).xyz;
	normal = vec3(model * vec4(vertNormal, 1)).xyz;
	gl_Position = proj * view * model * vec4(vertPos, 1);
}