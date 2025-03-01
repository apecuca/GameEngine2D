#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject& parent);
	virtual ~Component() = default;

	// 
	Component(const Component& other) :
		Component(other.gameObject) {}
	Component(Component&& other) = default;

	// 
	Component& operator = (const Component& other) { return *this; }
	Component& operator = (Component&& other) = default;

	// 
	bool operator == (const Component& other) const
	{
		return (other.GetUniqueID() == this->GetUniqueID());
	}

	// 
	inline int GetUniqueID() const { return uniqueID; }

	bool enabled = true;
	GameObject& gameObject;

	virtual void Update();

protected:
	// Identificador
	int uniqueID;
	static int nextCreationID;
};

class GenericComponent : public Component
{
	GenericComponent(GameObject& parent);
	~GenericComponent() = default;

	void Update() override;
};