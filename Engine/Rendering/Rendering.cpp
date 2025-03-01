#include "Rendering.hpp"

// Engine
#include "../Debug.hpp"

// Statics
std::vector<std::reference_wrapper<RenderSource>> Rendering::renderSources;

void Rendering::Render()
{
	// Render all enabled sources
	for (int i = 0; i < renderSources.size(); i++)
	{
		if (!renderSources.at(i).get().enabled) continue;

		renderSources.at(i).get().Render();
	}
}

void Rendering::AddRenderSource(RenderSource& source)
{
	renderSources.emplace_back(source);
}

void Rendering::RemoveRenderSource(RenderSource& source)
{
	for (int i = 0; i < renderSources.size(); i++)
	{
		if (renderSources.at(i) != source)
			continue;

		renderSources.erase(renderSources.begin() + i);
	}
}