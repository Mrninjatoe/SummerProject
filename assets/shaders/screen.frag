#version 440 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D sceneTexture;

void main(){
	fragColor = texture(sceneTexture, texCoords);
}