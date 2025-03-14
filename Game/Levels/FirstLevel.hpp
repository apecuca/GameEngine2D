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
		player = std::make_unique<GameObject>(LevelManager::Instantiate());
		player->AddComponent<RenderSource>(); // Add the component RenderSource to the player gameobject
		// Save a reference to the component RenderSource from the player's gameobject
		std::unique_ptr<RenderSource>& rnd = player->GetComponent<RenderSource>();
		rnd->InitShader("b_sprite.vert", "b_sprite.frag"); // Initializes the shader (vertex and fragment)
		rnd->SetRenderOrder(playerRenderOrder);
		rnd->currentSpriteId = Rendering::PoolSprite("Lupi.png"); // Update the current sprite to render
	
		// First enemy (top right)
		GameObject& enemy = LevelManager::Instantiate();
		std::unique_ptr<RenderSource>& rnd2 = enemy.AddComponent<RenderSource>();
		rnd2->InitShader("b_sprite.vert", "b_sprite.frag");
		rnd2->SetRenderOrder(1);
		enemy.position = glm::vec3(1.0, 1.0, 0.0);

		// Second enemy (bottom left)
		GameObject& enemy2 = LevelManager::Instantiate();
		std::unique_ptr<RenderSource>& rnd3 = enemy2.AddComponent<RenderSource>();
		rnd3->InitShader("b_sprite.vert", "b_sprite.frag");
		rnd3->SetRenderOrder(5);
		enemy2.position = glm::vec3(-1.0, -1.0, 0.0);
	};

	void CustomUpdate() override
	{
		float _newTime = (float)glfwGetTime();
		deltaTime = _newTime - lastTime;
		lastTime = _newTime;

		timer += 1.0f * deltaTime;
		if (timer < 1.0f) return;
		//

		playerRenderOrder = playerRenderOrder == 0 ? 2 : 0;
		player->GetComponent<RenderSource>()->SetRenderOrder(playerRenderOrder);

		//
		timer -= 1.0f;
	};

private:
	std::unique_ptr<GameObject> player;
	int playerRenderOrder {0};
	float deltaTime, lastTime, timer;
};