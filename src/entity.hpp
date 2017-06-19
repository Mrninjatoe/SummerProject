#pragma once
#include <map>
#include <typeindex>
#include <string>
#include "components/component.hpp"

class Component;

class Entity {
public:
	~Entity();

	template <typename T>
	void addComponent(T c) {
		_components[std::type_index(typeid(T))] = (Component*)c;
	}
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
	void update(float delta);
private:
	std::string _type;
	std::map<std::type_index, Component*> _components;
};