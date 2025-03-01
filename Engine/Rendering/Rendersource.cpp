#include "Rendersource.hpp"

// Engine 
#include "Rendering.hpp"
#include "../Debug.hpp"
#include "Shader.hpp"

// Statics
int RenderSource::nextCreationID = 0;

RenderSource::RenderSource(GameObject& parent) :
	Component(parent),
	uniqueID { nextCreationID },
	enabled { true }
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
	
	shader->Draw();
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

void RenderSource::AddSprite(const std::string& fileName, bool gamma)
{
	shader->LoadTextureFromFile(fileName, false);
}