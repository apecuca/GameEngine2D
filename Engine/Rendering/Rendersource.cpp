#include "Rendersource.hpp"

// Engine 
#include "Rendering.hpp"
#include "../Debug.hpp"
#include "Shader.hpp"

RenderSource::RenderSource(GameObject& parent) : Component(parent),
	color(glm::vec4(1.0f))
{
	Rendering::AddRenderSource(this);
}

RenderSource::~RenderSource()
{
	Rendering::RemoveRenderSource(this);
}

void RenderSource::Render()
{
	if (shader == NULL) return;
	
	// Update shader settings
	shader->SetVec4("color", color);

	shader->Draw(currentSpriteId);
}

void RenderSource::InitShader(const char* vertex, const char* fragment)
{
	if (shader != nullptr)
	{
		Debug::Log("Shader already initialized!");
		return;
	}

	shader = std::make_unique<Shader>(vertex, fragment, gameObject);
}

void RenderSource::SetRenderOrder(const int& value)
{
	renderOrder = value;
	Rendering::OnRenderOrderChanged();
}