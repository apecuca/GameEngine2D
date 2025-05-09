#include "Rendering.hpp"

// Standard
#include <algorithm>

// Externals
#include "stb_image.h"

// Engine
#include "../Debug.hpp"

// Statics
std::vector<RenderSource*> Rendering::renderSources;
std::vector<std::unique_ptr<Sprite>> Rendering::pooledSprites;

void Rendering::Init()
{
    // Pool default sprite
    PoolSprite("Default.png", 32);
}

void Rendering::Render()
{
	// Render all enabled sources
	for (int i = 0; i < renderSources.size(); i++)
	{
		if (!renderSources.at(i)->enabled) continue;

		renderSources.at(i)->Render();
	}
}

void Rendering::AddRenderSource(RenderSource* source)
{
	renderSources.emplace_back(source);
}

void Rendering::RemoveRenderSource(RenderSource* source)
{
	for (int i = 0; i < renderSources.size(); i++)
	{
		if (renderSources.at(i) != source)
			continue;

		renderSources.erase(renderSources.begin() + i);
	}
}

int Rendering::PoolSprite(const char* fileName, float pixelsPerUnit)
{
    // Emplace the new sprite id on the back
    pooledSprites.push_back(
        std::make_unique<Sprite>(fileName, pixelsPerUnit));
        //LoadTextureFromFile(fileName, false));

    // Return id of the newly emplaced sprite
    return static_cast<int>(pooledSprites.size() - 1);
}

Sprite* Rendering::GetPooledSprite(const int& id)
{
    // If it's not a valid ID, return default texture
    if (id >= pooledSprites.size() || id < 0)
        return 0;

    return pooledSprites[id].get();
}

void Rendering::ClearSpritePool()
{
    pooledSprites.clear();
}

void Rendering::OnRenderOrderChanged()
{
    // std::sort's algorith sorts everything inside the vector
    // In the future, I'll rewrite this with a custom algorith to sort
    // only the changed source
    std::sort(std::begin(renderSources), std::end(renderSources), 
        [](const RenderSource* vecA, const RenderSource* vecB) -> bool {
            return vecA->GetRenderOrder() < vecB->GetRenderOrder();
        });
}