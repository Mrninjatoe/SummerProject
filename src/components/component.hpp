#pragma once

class Component {
public:
	virtual ~Component();
	virtual void update(float delta) = 0;
private:

};