#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "glm/glm.hpp"

#include "Component.hpp"

class GameObject
{
public:
	//
	GameObject();
	~GameObject();

	//
	GameObject(const GameObject& other) :
		uniqueID{ nextCreationID } {}
	GameObject(GameObject&& other) = default;

	//
	GameObject& operator = (const GameObject& other) { return *this; }
	GameObject& operator = (GameObject&& other) = default;

	//
	bool operator == (const GameObject& other) const
	{
		return (other.GetUniqueID() == this->GetUniqueID());
	}

	//
	inline int GetUniqueID() const { return uniqueID; }

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
	std::unique_ptr<T>& AddComponent()
	{
		if (components.size() - 1 >= components.capacity())
		{
			components.reserve(4);
		}

		components.push_back(std::make_unique<T>(*this));

		return reinterpret_cast<std::unique_ptr<T>&>(components[components.size() - 1]);
	}

	template <class T>
	std::unique_ptr<T>& GetComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (typeid(T).name() != typeid(*components.at(i).get()).name())
				continue;

			return reinterpret_cast<std::unique_ptr<T>&>(components[i]);
		}

		throw std::runtime_error("No component of type found in object");
	}

	/*
	// 
	template <class T> 
	std::shared_ptr<T> AddComponent()
	{
		if (components.size() - 1 >= components.capacity())
		{
			components.reserve(4);
		}

		std::shared_ptr<T> newComponent = std::make_shared<T>(*this);
		components.push_back(newComponent);

		return newComponent;
	}

	// 
	template <class T> 
	auto GetComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (typeid(T).name() != typeid(*components.at(i).get()).name())
				continue;

			return components.at(i);
		}

		throw std::runtime_error("No component of type found in object");
	}
	*/

private:
	// 
	int uniqueID;
	static int nextCreationID;

	//
	glm::vec3 lastRotation = glm::vec3(0.f);

	// 
	std::vector<std::unique_ptr<Component>> components;

	void UpdateRotation(const glm::vec3& lastOperation);
};