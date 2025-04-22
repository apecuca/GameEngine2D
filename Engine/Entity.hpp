#pragma once

class Entity {
public:
	Entity() : uniqueID{ nextCreationID++ } {}
	virtual ~Entity() = default;

	// Comparison operation
	bool operator == (const Entity& other) const {
		return (other.uniqueID == this->uniqueID);
	}

	bool operator != (const Entity& other) const {
		return (other.uniqueID != this->uniqueID);
	}

protected:
	// Identificador
	int uniqueID;
	inline static int nextCreationID = 0;
};