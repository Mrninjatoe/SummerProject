#pragma once
#include <map>
#include <typeindex>
#include <string>
#include "components/component.hpp"

class Component;

class Entity {
public:
	~Entity();
	virtual void render() = 0;

	void addComponent(std::type_index type, Component* c);
	template <typename T>
	T* get() {
		auto it = _components.find(std::type_index(typeid(T)));
		if (it != _components.end())
			return dynamic_cast<T*>(it->second);
		return nullptr;
	}

	void setType(const std::string& type) {
		_type = type;
	}

	std::string getType() const{
		return _type;
	}
private:
	std::string _type;
	std::map<std::type_index, Component*> _components;
};