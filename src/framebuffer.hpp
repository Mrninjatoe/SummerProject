#pragma once
#include "lib/glad.h"
#include <vector>

class FrameBuffer {
public:
	FrameBuffer();
	virtual ~FrameBuffer();
	FrameBuffer& addTexture(GLuint id, GLenum type, GLenum dataFormat, int sizeX, int sizeY, bool depth, GLenum format);
	FrameBuffer& bind();
	FrameBuffer& bindTexture(GLuint id);
private:
	GLuint _fbo;
	std::vector<GLuint> _textures;
};