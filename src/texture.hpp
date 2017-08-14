#pragma once
#include "lib/glad.h"
#include "SDL2/SDL_image.h"
#include <string>

class Texture {
public:
	Texture(const std::string& filePath);
	virtual ~Texture();
	void bind(int slot);
	GLuint getTexture() { return _texture; }
private:
	GLuint _texture;
	void _setData(GLenum format, GLuint w, GLuint h, const void* pixels);
};