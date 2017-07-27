#pragma once
#include "component.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class TransformComponent : public Component {
public:
	TransformComponent(glm::vec3 pos);
	virtual ~TransformComponent();
	virtual void update(float delta);
	glm::mat4 getModelMX() const { return _model; }
	void rotate(float angle, glm::vec3 axis);
	void move(glm::vec3 pos);
	void rescale(glm::vec3 scale);
private:
	glm::vec3 _rotation;
	glm::vec3 _scale;
	glm::vec3 _position;
	glm::mat4 _model;
	float _angle;
	bool _changed;

	void _fixModelMX();
};