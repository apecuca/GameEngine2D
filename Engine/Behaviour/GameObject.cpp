#include "GameObject.hpp"

int GameObject::nextCreationID = 0;

GameObject::GameObject() :
	uniqueID{ nextCreationID }
{
	nextCreationID++;
	this->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
}

GameObject::~GameObject()
{
	for (int i = static_cast<int>(components.size()) - 1; i >= 0; i--)
		components.at(i).reset();
}

void GameObject::UpdateBehaviour()
{
	for (int i = 0; i < components.size(); i++)
	{
		components.at(i)->Update();
	}
}

void GameObject::Rotate(const float& angle)
{
	SetRotation(glm::vec3(rotation.x, rotation.y, rotation.z + angle));
}

void GameObject::SetRotation(const glm::vec3& angle)
{
	rotation = angle;

	UpdateRotation(angle);
}

void GameObject::SetRotation(const glm::vec3& angle, const bool& clamp)
{
	rotation = angle;

	if (clamp)
		rotation.y = glm::clamp(rotation.y, -89.0f, 89.0f);

	UpdateRotation(angle);
}

void GameObject::UpdateRotation(const glm::vec3& lastOperation)
{
	// Gerenciamento
	lastRotation = lastOperation;

	// 
	front = glm::normalize(glm::vec3(
		cos(glm::radians(rotation.y)) * sin(glm::radians(rotation.x)),
		-sin(glm::radians(rotation.y)),
		cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
	));

	right = glm::normalize(glm::vec3(
		-cos(glm::radians(rotation.x)),
		0.f,
		sin(glm::radians(rotation.x))
	));

	up = glm::normalize(glm::vec3(
		sin(glm::radians(rotation.y)) * sin(glm::radians(rotation.x)),
		cos(glm::radians(rotation.y)),
		sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
	));
}