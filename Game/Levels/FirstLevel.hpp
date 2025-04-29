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
		player = LevelManager::Instantiate();
		RenderSource* rnd = player->AddComponent<RenderSource>();
		rnd->InitShader("b_sprite.vert", "b_sprite.frag"); // Initializes the shader (vertex and fragment)
		rnd->SetRenderOrder(playerRenderOrder);
		rnd->currentSpriteId = Rendering::PoolSprite("Lupi.png"); // Update the current sprite to render
	};

	void CustomUpdate() override
	{
		//
	};

private:
	GameObject* player;
	int playerRenderOrder{ 0 };
	float timer;
};