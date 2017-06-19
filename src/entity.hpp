#pragma once

class Entity {
public:
	Entity();
	~Entity();
	virtual void render() = 0;
private:

};