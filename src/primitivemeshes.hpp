#pragma once
#include "entity.hpp"
#include <glm/glm.hpp>
#include "lib/glad.h"
#include <vector>
class PrimitiveMeshes{
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texCoords;
	};
public:
	enum Primitives : int {TRIANGLE = 0, QUAD, PRISM};
	PrimitiveMeshes() {}
	PrimitiveMeshes(const std::string& fileName);
	PrimitiveMeshes(Primitives type);
	GLuint getVAO(){return _vao;}
	GLuint getVBO(){return _vbo;}
	GLuint getEBO(){return _ebo;}
	std::vector<unsigned int> getIndices() { return _indices; }
	std::vector<Vertex> getVertices() { return _vertices; }
	virtual ~PrimitiveMeshes();
private:
	std::vector<unsigned int> _indices;
	std::vector<Vertex> _vertices;
	GLuint _vao, _vbo, _ebo;

	void _createTriangle();
	void _createQuad();
	void _createPrism();
	void _loadMesh(const std::string& fileName);
	void _fixBuffers();
};