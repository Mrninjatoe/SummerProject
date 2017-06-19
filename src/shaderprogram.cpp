#include "shaderprogram.hpp"
#include <fstream>
#include <vector>

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath) {
	// Very ugly code, just wanted to make it quick.
	GLuint vertexID = _createShader(vertexPath, GL_VERTEX_SHADER);
	GLuint geometryID = NULL;
	if(geometryPath != "")
		geometryID = _createShader(geometryPath, GL_GEOMETRY_SHADER);
	GLuint fragID = _createShader(fragmentPath, GL_FRAGMENT_SHADER);
	
	_program = glCreateProgram();
	glAttachShader(_program, vertexID);
	if(geometryID != NULL)
		glAttachShader(_program, geometryID);
	glAttachShader(_program, fragID);
	
	glLinkProgram(_program);
	
	// Temporary debugger!
	GLint result;
	int info;
	glGetProgramiv(_program, GL_LINK_STATUS, &result);
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &info);
	if (info > 0) {
		std::vector<char> ProgramErrorMessage(info + 1);
		glGetProgramInfoLog(_program, info, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	// End of debugger lmao.

	glDetachShader(_program, vertexID);
	if (geometryID != NULL) {
		glDetachShader(_program, geometryID);
		glDeleteShader(geometryID);
	}
	glDetachShader(_program, fragID);

	glDeleteShader(vertexID);
	glDeleteShader(fragID);
}

ShaderProgram::~ShaderProgram() {
	
}

GLuint ShaderProgram::_createShader(const std::string& path, GLenum type) {
	GLuint id = glCreateShader(type);
	std::string shaderCode;
	std::ifstream shaderStream(path.c_str(), std::ios::in);
	if (shaderStream.is_open()) {
		std::string line = "";
		while (std::getline(shaderStream, line))
			shaderCode += "\n" + line;
		shaderStream.close();
	}
	else
		printf("Could not open file with path: %s\n", path.c_str());

	char const* srcPointer = shaderCode.c_str();
	glShaderSource(id, 1, &srcPointer, NULL);
	glCompileShader(id);
	
	return id;
}

ShaderProgram& ShaderProgram::addUniform(const std::string& name) {
	GLint location = glGetUniformLocation(_program, name.c_str());
	_uniform[name] = location;
	return *this;
}

ShaderProgram& ShaderProgram::bind() {
	glUseProgram(_program);
	return *this;
}