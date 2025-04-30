#pragma once

#include "../Engine/Engine.hpp"

class FirstLevel : public Level
{
public:
	FirstLevel() : Level(),
		timer{ 0.0f }
	{
		Debug::Log("Level loaded!!");
	};

	void OnLevelInit() override
	{
		rnd = LevelManager::Instantiate()->AddComponent<RenderSource>();
		rnd->InitShader("b_sprite.vert", "b_sprite.frag"); // Initializes the shader (vertex and fragment)
		rnd->currentSpriteId = Rendering::PoolSprite("Lupi.png", 688.5); // Update the current sprite to render
	};

	void CustomUpdate() override
	{
		//
	};

private:
	RenderSource* rnd;
	float timer;
};