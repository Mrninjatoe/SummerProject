#pragma once
#include <memory>
#include "component.hpp"
#include "../entities/primitivemeshes.hpp"

class ModelComponent : public Component {
public:
	ModelComponent(PrimitiveMeshes::Primitives type);
	ModelComponent(const std::string& fileName);
	virtual ~ModelComponent();
	virtual void update(float delta);
	void render();
	void render(glm::mat4 m);
protected:
	std::shared_ptr<PrimitiveMeshes> _mesh;
private:

};