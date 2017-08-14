#pragma once
#include <vector>
#include <memory>
#include "entity.hpp"
#include "components/modelcomponent.hpp"
#include "entities/blockchunk.hpp"

class World {
public:
	World();
	virtual ~World();
	void update(float delta);
	void render();
	std::shared_ptr<Entity> createEntity(glm::vec3 pos);
private:
	std::vector<std::shared_ptr<Entity>> _entities;
};