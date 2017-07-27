#pragma once
#include "component.hpp"
#include "glm/glm.hpp"

class CameraComponent : public Component {
public:
	CameraComponent();
	virtual ~CameraComponent();
	void update(float delta);
	glm::mat4 getProjMX() const {return _projection;}
	glm::mat4 getViewMX() const {return _view;}
	glm::vec3 getCameraPos() const { return _cameraPos; }
	void setCameraPos(glm::vec3 cameraPos);
	void setLookAt(glm::vec3 lookAt);
private:
	glm::mat4 _projection;
	glm::mat4 _view;
	glm::vec3 _cameraPos;
	glm::vec3 _lookAt;
	glm::vec3 _right;
	glm::vec3 _up;

	void _calculateUp();
};