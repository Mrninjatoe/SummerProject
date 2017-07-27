#pragma once
#include <map>
#include <typeindex>
#include <string>
#include "components/component.hpp"
#include <iostream>

class Entity {
public:
	~Entity();

	template <typename T>
	void addComponent(std::type_index type, T c) {
		_components[type] = (Component*)c;
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