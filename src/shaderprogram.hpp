#pragma once
#include "lib/glad.h"
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
public:
	ShaderProgram() {}
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
	virtual ~ShaderProgram();
	ShaderProgram& bind();
	ShaderProgram& addUniform(const std::string& name);
	template <typename T>
	ShaderProgram& setUniform(const std::string& name, const T& value) {
		_glUniform(_uniform.at(name), 1, &value);
		return *this;
	}
private:
	GLuint _program;
	std::map<std::string, GLint> _uniform;
	GLuint _createShader(const std::string& path, GLenum type);
	
	static void _glUniform(GLuint id, GLuint count, const GLfloat* data) { glUniform1fv(id, count, data); };
	static void _glUniform(GLuint id, GLuint count, const glm::vec2* data) { glUniform2fv(id, count, glm::value_ptr(data[0])); };
	static void _glUniform(GLuint id, GLuint count, const glm::vec3* data) { glUniform3fv(id, count, glm::value_ptr(data[0])); };
	static void _glUniform(GLuint id, GLuint count, const glm::mat3* data) { glUniformMatrix3fv(id, count, GL_FALSE, glm::value_ptr(data[0])); };
	static void _glUniform(GLuint id, GLuint count, const glm::mat4* data) { glUniformMatrix4fv(id, count, GL_FALSE, glm::value_ptr(data[0])); };
};