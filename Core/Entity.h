#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>
#include <typeindex>

#include "Scripts.h"

#include "GraphicsComponent.h"
#include "NpcComponent.h"

// Forward declaration
class Component;

// Main Entity
class Entity {
public:

	~Entity();

	void addComp(std::type_index type, Component* c);

	template <typename T>
	T* get() {
		auto it = components.find(std::type_index(typeid(T)));
		if (it != components.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return nullptr;
	}

	void setType(const std::string& type) {
		this->type = type;
	}

	std::string getType() const {
		return type;
	}

	void update(float);
	void render(sf::RenderWindow*, const sf::Time&);

private:
	std::string type;
	std::map<std::type_index, Component*> components;
};

template <typename T>
static void addComponent(Entity* e, sol::table& componentTable) {
	e->addComp(std::type_index(typeid(T)), new T(componentTable));
}
#endif