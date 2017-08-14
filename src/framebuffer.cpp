#include "framebuffer.hpp"

FrameBuffer::FrameBuffer() {
	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &_fbo);
}

FrameBuffer& FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	return *this;
}

FrameBuffer& FrameBuffer::bindTexture(GLuint id) {
	glBindTexture(GL_TEXTURE_2D, _textures[id]);
	return *this;
}

FrameBuffer& FrameBuffer::addTexture(GLuint id, GLenum type, GLenum dataFormat, int sizeX, int sizeY, bool depth, GLenum format){
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(type, texture);
	
	glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, sizeX, sizeY, 0, dataFormat, format, 0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + id, GL_TEXTURE_2D, texture, 0);
	
	// TO-DO: Finish depth for later usage.
	if (depth) {
		GLuint depthBuffer;
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, sizeX, sizeY);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	}
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("ERROR, FRAMEBUFFER IS NOT COMPLETE!\n");
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	_textures.push_back(texture);
	return *this;
}