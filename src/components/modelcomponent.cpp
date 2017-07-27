#include "modelcomponent.hpp"

ModelComponent::ModelComponent(PrimitiveMeshes::Primitives type) {
	_mesh = std::make_shared<PrimitiveMeshes>(type);

}

ModelComponent::ModelComponent(const std::string& fileName) {
	_mesh = std::make_shared<PrimitiveMeshes>(fileName);
}

ModelComponent::~ModelComponent() {
	
}

void ModelComponent::update(float delta) {
	// Make it good with instancing...
	glBindVertexArray(_mesh->getVAO());
	glDrawElementsInstanced(GL_TRIANGLES, _mesh->getIndices().size(), GL_UNSIGNED_INT, NULL, 1);
}

void ModelComponent::render() {
	glBindVertexArray(_mesh->getVAO());
	glDrawElementsInstanced(GL_TRIANGLES, _mesh->getIndices().size(), GL_UNSIGNED_INT, NULL, 1);
}

void ModelComponent::render(glm::mat4 m) {
	glBindVertexArray(_mesh->getVAO());
	glDrawElementsInstanced(GL_TRIANGLES, _mesh->getIndices().size(), GL_UNSIGNED_INT, NULL, 1);
}