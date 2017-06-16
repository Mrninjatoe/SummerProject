#pragma once
#include "lib/glad.h"
#include <string>

class ShaderProgram {
public:
	ShaderProgram() {}
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
	virtual ~ShaderProgram();
	ShaderProgram& bind();
private:
	GLuint _program;
	GLuint _createShader(const std::string& path, GLenum type);
};