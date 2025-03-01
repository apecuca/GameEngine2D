#pragma once

#include <vector>
#include "Rendersource.hpp"

class Rendering
{
public:
	// Render call, don't call this manually
	static void Render();

	// Add a new render source
	static void AddRenderSource(RenderSource& source);
	// Remove a render source
	static void RemoveRenderSource(RenderSource& source);

private:
	// Renderer list
	static std::vector<std::reference_wrapper<RenderSource>> renderSources;
};