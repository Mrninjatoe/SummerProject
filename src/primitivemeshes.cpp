#include "primitivemeshes.hpp"

PrimitiveMeshes::PrimitiveMeshes(PrimitiveMeshes::Primitives type) {
	switch (type) {
	case Primitives::TRIANGLE:
		_createTriangle();
		break;
	case Primitives::QUAD:
		_createQuad();
		break;
	default:
		break;
	}
}

PrimitiveMeshes::~PrimitiveMeshes() {
	
}

void PrimitiveMeshes::render() {
	glBindVertexArray(_vao);
	glDrawElementsInstanced(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, NULL, 20);
}

void PrimitiveMeshes::_createTriangle() {
	_vertices.push_back(
		Vertex{
			glm::vec3(-1.0f, -1.0f, 0.0f),
			glm::vec3(1.0f, -1.0f, 0.0f),
			glm::vec3(1.0f, 0.f, 0.f),
			glm::vec2(0.0f, 0.0f)
		}
	);
	_vertices.push_back(
		Vertex{
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, 1.f, 0.f),
		glm::vec2(0.0f, 0.0f)
		}
	);
	_vertices.push_back(
		Vertex{
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(.0f, 1.f, 1.f),
		glm::vec2(0.0f, 0.0f)
		}
	);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);

	_fixBuffers();
}

void PrimitiveMeshes::_createQuad() {
	
}

void PrimitiveMeshes::_fixBuffers() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int),
		&_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::color));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::texCoords));

	glBindVertexArray(0);
}