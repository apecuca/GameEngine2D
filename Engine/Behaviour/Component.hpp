#pragma once

#include "../Entity.hpp"

class GameObject;

class Component : public Entity
{
public:
	Component(GameObject& parent);
	virtual ~Component() = default;

	// 
	Component(Component& other) :
		Component(other.gameObject) {}
	Component(Component&& other) = default;

	// 
	Component& operator = (const Component& other) { return *this; }
	Component& operator = (Component&& other) = default;

	bool enabled = true;
	GameObject& gameObject;

	virtual inline void Update() {};
};

class GenericComponent : public Component
{
public:
	GenericComponent(GameObject& parent);
	~GenericComponent() = default;

	void Update() override;
};