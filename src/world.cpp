#include "world.hpp"

World::World() {
	auto e = createEntity();
	e->addComponent(new ModelComponent("assets/models/cube.obj"));
	_entities.push_back(e);
}

World::~World() {
	
}

void World::update(float delta) {
	for (std::shared_ptr<Entity> e : _entities) {
		e->update(delta);
	}
}

std::shared_ptr<Entity> World::createEntity() {
	std::shared_ptr<Entity> e = std::make_shared<Entity>();

	return e;
}