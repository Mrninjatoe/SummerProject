#pragma once
#include "entity.hpp"
#include <glm/glm.hpp>
#include "lib/glad.h"
#include <vector>
class PrimitiveMeshes : public Entity {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texCoords;
	};
public:
	enum Primitives : int {TRIANGLE = 0, QUAD};
	PrimitiveMeshes(Primitives type);
	virtual ~PrimitiveMeshes();
	virtual void render();
private:
	std::vector<unsigned int> _indices;
	std::vector<Vertex> _vertices;
	GLuint _vao, _vbo, _ebo;

	void _createTriangle();
	void _createQuad();
	void _fixBuffers();
};