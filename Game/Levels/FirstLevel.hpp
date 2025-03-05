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
		// Instantiate and save a reference to the GameObject of the player
		player = std::make_shared<GameObject>(LevelManager::Instantiate());
		player->AddComponent<RenderSource>(); // Add the component RenderSource to the player gameobject
		// Save a reference to the component RenderSource from the player's gameobject
		std::unique_ptr<RenderSource>& rnd = player->GetComponent<RenderSource>();
		rnd->InitShader("b_sprite.vert", "b_sprite.frag"); // Initializes the shader (vertex and fragment)
		rnd->currentSpriteId = Rendering::PoolSprite("Lupi.png"); // Update the current sprite to render
	};

	void CustomUpdate() override
	{
		// This just updates the current sprite every few seconds,
		// just testing if it's working

		float _sin = glm::sin((float)glfwGetTime());

		if (_sin >= 0.0f)
			player->GetComponent<RenderSource>()->currentSpriteId = 1;
		else
			player->GetComponent<RenderSource>()->currentSpriteId = 0;
	};

private:
	std::shared_ptr<GameObject> player;
};