#include "cameracomponent.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../engine.hpp"

CameraComponent::CameraComponent() {
	_cameraPos = glm::vec3(0, 0, 0);
	_lookAt = glm::vec3(0, 0, 0);
	_up = glm::vec3(0, 1, 0);
	_projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	_view = glm::lookAt(_cameraPos, _lookAt, _up);
}

CameraComponent::~CameraComponent() {

}

void CameraComponent::update(float delta) {
	auto shader = Engine::getInstance().getShader();
	shader->bind().setUniform("proj", _projection)
		.setUniform("view", _view);
}

void CameraComponent::setCameraPos(glm::vec3 cameraPos) {
	_cameraPos = cameraPos;
	_calculateUp();
	_view = glm::lookAt(_cameraPos, _lookAt, _up);
}

void CameraComponent::setLookAt(glm::vec3 lookAt) {
	_lookAt = lookAt;
	_calculateUp();
	_view = glm::lookAt(_cameraPos, lookAt, glm::vec3(1, 0, 0));
}

void CameraComponent::_calculateUp() {
	glm::vec3 tempUp = glm::vec3(0, 1, 0);
	glm::vec3 dir = glm::normalize(_cameraPos - _lookAt);
	_right = glm::cross(dir, tempUp);
	_up = glm::cross(_right, dir);
}