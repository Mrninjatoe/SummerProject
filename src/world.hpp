#pragma once
#include <vector>
#include <memory>
#include "entity.hpp"
#include "components/modelcomponent.hpp"

class World {
public:
	World();
	virtual ~World();
	void update(float delta);
	std::shared_ptr<Entity> createEntity();
private:
	std::vector<std::shared_ptr<Entity>> _entities;
};