#version 440 core
in vec3 color;
in vec3 worldPos;
in vec3 normal;
in vec2 uv;
in vec2 textureCoords1;
in vec2 textureCoords2;
in float blend;

out vec4 outColor;

uniform vec3 lightPos;
uniform vec3 particleColor;
uniform sampler2D partAtlas;

void main(){
	vec4 color1 = texture(partAtlas, textureCoords1);
	vec4 color2 = texture(partAtlas, textureCoords2);

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - worldPos);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1, 1, 1);

	float ambStr = 0.1f;
	vec3 ambient = ambStr * vec3(1, 1, 1);

	vec3 result = (diffuse + ambient) * color;
	outColor = vec4(mix(color1.xyz, color2.xyz, blend) * vec3(0,1,0), 1);
}