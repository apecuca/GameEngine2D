#pragma once

// Standard
#include <vector>

// External
#include "../CommonInclude/CommonRender.hpp"

// Engine
#include "Rendersource.hpp"
#include "Sprite.hpp"

class Window;

class Rendering
{
public:
	// Initit call for rendering services, don't call this manually
	static void Init();

	// Render call, don't call this manually
	static void Render(std::unique_ptr<Window>& window);

	// Add a new render source
	static void AddRenderSource(RenderSource* source);
	// Remove a render source
	static void RemoveRenderSource(RenderSource* source);

	//
	// Sprite pooling
	//

	// Pool sprite for multiple uses, returns identifier of pooled sprite
	static int PoolSprite(const char* fileName, float pixelsPerUnit);

	static const Sprite& GetPooledSprite(const int& id);

	static void ClearSpritePool();

	// Called when a rendering order is changed, don't call this manually
	static void OnRenderOrderChanged();
	// Update framebuffer's size to new screen size, don't call this manually
	static void ResizeFramebuffer();

private:
	static void GenerateBuffers();

private:
	// Avoids object creation
	Rendering();
	
	// Frame Buffer Object, Frame Buffer Texture, Render Buffer Object
	static GLuint FBO, FBT, RBO;
	static GLuint screenquadVAO, screenquadVBO;
	static std::unique_ptr<Shader> screenShader;

	// Renderer list
	static std::vector<RenderSource*> renderSources;

	// List with id of pooled textures
	static std::vector<std::unique_ptr<Sprite>> pooledSprites;
};