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

	// Render call for sources, don't call this manually!!
	void Render();

	// Initialize shader for this render source
	void InitShader(const char* vertex, const char* fragment);

	// Extra details
	bool enabled {true};

	// This will be moved to another place
	int currentSpriteId {0};

	// 
	// Render order stuff
	//

	void SetRenderOrder(const int& value);
	inline int GetRenderOrder() const { return renderOrder; }

private:
	std::unique_ptr<Shader> shader;
	int renderOrder {0};

}; // Class