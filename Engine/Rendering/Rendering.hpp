#pragma once

// Standard
#include <vector>

// External
#include "../CommonInclude/CommonRender.hpp"

// Engine
#include "Rendersource.hpp"
#include "Sprite.hpp"

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

	static int PoolSprite(const char* fileName, float pixelsPerUnit);

	static Sprite* GetPooledSprite(const int& id);

	static void ClearSpritePool();

	// Called when a rendering order is changed, don't call this manually
	static void OnRenderOrderChanged();


private:
	// Avoids object creation
	Rendering();

	// Renderer list
	static std::vector<RenderSource*> renderSources;

	// List with id of pooled textures
	static std::vector<std::unique_ptr<Sprite>> pooledSprites;
};