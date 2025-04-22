#pragma once

// Standard
#include <vector>

// External
#include "../CommonInclude/CommonRender.hpp"

// Engine
#include "Rendersource.hpp"

class Rendering
{
public:
	// Initit call for rendering services, don't call this manually
	static void Init();

	// Render call, don't call this manually
	static void Render();

	// Add a new render source
	static void AddRenderSource(RenderSource* source);
	// Remove a render source
	static void RemoveRenderSource(RenderSource* source);

	//
	// Sprite pooling
	//

	static int PoolSprite(const char* fileName);

	static GLuint GetPooledSprite(const int& id);

	static void ClearSpritePool();

	// Called when a rendering order is changed, don't call this manually
	static void OnRenderOrderChanged();


private:
	// Avoids object creation
	Rendering();

	// Renderer list
	static std::vector<RenderSource*> renderSources;

	// List with id of pooled textures
	static std::vector<GLuint> pooledSprites;

	static GLuint LoadTextureFromFile(const std::string& file, bool gamma = false);
};