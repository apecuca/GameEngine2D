#pragma once

// Standard libraries
#include <memory>
#include <iostream>

// Engine classes
#include "../Behaviour/Component.hpp"

// Forward declaration
class Shader;

class RenderSource : public Component
{
public:
	// Default constructor and destructor
	RenderSource(GameObject& parent);
	~RenderSource();

	// Comparison operation
	bool operator == (const RenderSource& other) const
	{
		return (other.GetUniqueID() == this->GetUniqueID());
	}

	// Render call for sources, don't call this manually!!
	void Render();

	// UniqueID getter
	inline int GetUniqueID() const { return uniqueID; }

	// Initialize shader for this render source
	void InitShader(const char* vertex, const char* fragment);

	// Extra details
	bool enabled = true;

	// This will be moved to another place
	int currentSpriteId = 0;

protected:
	// Unique Identifier
	int uniqueID;
	static int nextCreationID;

private:
	std::shared_ptr<Shader> shader;

}; // Class