#include "Rendersource.hpp"

// Engine 
#include "Rendering.hpp"
#include "../Debug.hpp"
#include "Shader.hpp"

// Statics
int RenderSource::nextCreationID = 0;

RenderSource::RenderSource(GameObject& parent) :
	Component(parent),
	uniqueID { nextCreationID }
{
	// UniqueID handling
	nextCreationID++;
	Rendering::AddRenderSource(*this);
}

RenderSource::~RenderSource()
{
	Rendering::RemoveRenderSource(*this);
}

void RenderSource::Render()
{
	if (shader == NULL) return;
	
	shader->Draw(currentSpriteId);
}

void RenderSource::InitShader(const char* vertex, const char* fragment)
{
	if (shader != NULL)
	{
		Debug::Log("Shader already initialized!");
		return;
	}

	shader = std::make_shared<Shader>(vertex, fragment, gameObject);
}