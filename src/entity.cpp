#include "entity.hpp"

Entity::~Entity() {
	for (auto& c : _components) {
		delete c.second;
	}
}

void Entity::update(float delta) {
	for (auto&c : _components) {
		c.second->update(delta);
	}
}