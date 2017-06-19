#pragma once
#include <memory>
#include "component.hpp"
#include "../primitivemeshes.hpp"

class ModelComponent : public Component {
public:
	ModelComponent(PrimitiveMeshes::Primitives type);
	ModelComponent(const std::string& fileName);
	virtual ~ModelComponent();
	virtual void update(float delta);
	PrimitiveMeshes* getMesh() const;
	void render();
protected:
	std::shared_ptr<PrimitiveMeshes> _mesh;
private:

};