#include "entity.hpp"

Entity::~Entity() {
	for (auto& c : _components) {
		delete c.second;
	}
}

void Entity::addComponent(std::type_index type, Component* c) {
	_components[type] = c;
}