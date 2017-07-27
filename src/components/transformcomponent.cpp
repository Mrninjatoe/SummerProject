#include "transformcomponent.hpp"
#include <iostream>

TransformComponent::TransformComponent(glm::vec3 pos) {
	_rotation = glm::vec3(0, 1, 0);
	_position = pos;
	_scale = glm::vec3(1);
	_angle = 0.f;
	_changed = true;
}

TransformComponent::~TransformComponent() {
	
}

void TransformComponent::update(float delta) {
	if (_changed)
		_fixModelMX();
}

void TransformComponent::_fixModelMX() {
	_model = glm::translate(_position) * glm::rotate(_angle, _rotation) * glm::scale(_scale);
	_changed = false;
}

void TransformComponent::rotate(float angle, glm::vec3 axis) {
	_angle += angle;
	_rotation = axis;
	_changed = true;
}

void TransformComponent::move(glm::vec3 pos) {
	_position += pos;
	_changed = true;
}

void TransformComponent::rescale(glm::vec3 scale) {
	_scale = scale;
	_changed = true;
}