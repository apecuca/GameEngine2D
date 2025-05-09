#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "glm/glm.hpp"

#include "Component.hpp"

class GameObject : public Entity
{
public:
	//
	GameObject();
	~GameObject();

	//
	GameObject(const GameObject& other) {}
	GameObject(GameObject&& other) = default;

	//
	GameObject& operator = (const GameObject& other) { return *this; }
	GameObject& operator = (GameObject&& other) = default;

	//
	glm::vec3 position = glm::vec3(0.0f);
	//
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	// 
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	void UpdateBehaviour();

	//
	void SetRotation(const glm::vec3& angle);
	void SetRotation(const glm::vec3& angle, const bool& clamp);
	void Rotate(const float& angle);

	template <class T>
	T* AddComponent()
	{
		if (components.size() - 1 >= components.capacity())
		{
			components.reserve(4);
		}

		components.push_back(std::make_unique<T>(*this));

		return dynamic_cast<T*>(components.back().get());
	}

	template <class T>
	T* GetComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (typeid(T).name() != typeid(*components.at(i).get()).name())
				continue;

			return dynamic_cast<T*>(components[i].get());
		}

		throw std::string("No component of type found in object");
	}

private:
	//
	glm::vec3 lastRotation = glm::vec3(0.f);

	// 
	std::vector<std::unique_ptr<Component>> components;

	void UpdateRotation(const glm::vec3& lastOperation);
};