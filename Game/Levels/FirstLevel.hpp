#pragma once

#include "../Engine/Engine.hpp"

class FirstLevel : public Level
{
public:
	FirstLevel() : Level()
	{
		Debug::Log("Level loaded!!");
	};

	void OnLevelInit() override
	{
		// Initialize player
		player = std::make_shared<GameObject>(LevelManager::Instantiate());
		player->AddComponent<RenderSource>();
		std::unique_ptr<RenderSource>& renderSource = player->GetComponent<RenderSource>();
		renderSource->InitShader("b_sprite.vert", "b_sprite.frag");
		renderSource->AddSprite("Lupi.png");
	};

	void CustomUpdate() override
	{
		player->Rotate(10.0f * 0.16f);
	};

private:
	std::shared_ptr<GameObject> player;
};