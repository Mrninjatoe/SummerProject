#include "texture.hpp"


Texture::Texture(const std::string& filePath) {
	SDL_Surface* surface = IMG_Load(filePath.c_str());

	if (!surface)
		printf("Couldn't load texture! %s\n", filePath.c_str());

	GLenum format;
	int nrOfColors = surface->format->BytesPerPixel;
	if (nrOfColors == 4) {
		if (surface->format->Rmask == 0x000000ff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}else if (nrOfColors == 3) {
		if (surface->format->Rmask == 0x000000ff)
			format = GL_RGB;
		else
			format = GL_BGR;
	}
	else {
		SDL_Surface* newSurf = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB24, 0);
		if (!newSurf)
			printf("Unknown texture format for file: %s\n", filePath.c_str());
		SDL_FreeSurface(surface);
		surface = newSurf;
		format = GL_RGB;
	}
	_setData(format, surface->w, surface->h, surface->pixels);

	SDL_FreeSurface(surface);
}

Texture::~Texture(){
	
}

void Texture::bind(int slot) {
	glBindTexture(GL_TEXTURE_2D, _texture);
}

void Texture::_setData(GLenum format, GLuint w, GLuint h, const void * pixels){
	glGenTextures(1, &_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, format, GL_UNSIGNED_BYTE, pixels);
}
