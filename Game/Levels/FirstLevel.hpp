#pragma once

#include "Engine.hpp"

class FirstLevel : public Level
{
public:
	FirstLevel() : Level(),
		player{ nullptr }
	{
		Debug::Log("Level loaded!!");
	};

	void OnLevelInit() override
	{
		player = LevelManager::Instantiate();
		RenderSource* rnd = player->AddComponent<RenderSource>();
		rnd->InitShader("b_sprite.vert", "b_sprite.frag"); // Initializes the shader (vertex and fragment)
		rnd->currentSpriteId = Rendering::PoolSprite("Lupi.png", 688.5); // Update the current sprite to render

		Animator* anim = player->AddComponent<Animator>();
	};

	void CustomUpdate() override
	{
		player->position.x += Input::horizontal * mvSpeed * Time::deltaTime;
		player->position.y += Input::vertical * mvSpeed * Time::deltaTime;
	};

private:
	GameObject* player;
	float mvSpeed = 5.0f;;
};