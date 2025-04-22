#pragma once

#include "../Engine/Engine.hpp"

class FirstLevel : public Level
{
public:
	FirstLevel() : Level(),
		deltaTime{ 0.0f }, lastTime{ 0.0f }, timer{ 0.0f }
	{
		Debug::Log("Level loaded!!");
	};

	void OnLevelInit() override
	{
		player = LevelManager::Instantiate();
		player->AddComponent<RenderSource>();
		RenderSource* rnd = player->GetComponent<RenderSource>();
		rnd->InitShader("b_sprite.vert", "b_sprite.frag"); // Initializes the shader (vertex and fragment)
		rnd->SetRenderOrder(playerRenderOrder);
		rnd->currentSpriteId = Rendering::PoolSprite("Lupi.png"); // Update the current sprite to render

		// First enemy (top right)
		enemy1 = LevelManager::Instantiate();
		RenderSource* rnd2 = enemy1->AddComponent<RenderSource>();
		rnd2->InitShader("b_sprite.vert", "b_sprite.frag");
		rnd2->SetRenderOrder(1);
		enemy1->position = glm::vec3(1.0, 1.0, 0.0);

		// Second enemy (bottom left)
		enemy2 = LevelManager::Instantiate();
		RenderSource* rnd3 = enemy2->AddComponent<RenderSource>();
		rnd3->InitShader("b_sprite.vert", "b_sprite.frag");
		rnd3->SetRenderOrder(5);
		enemy2->position = glm::vec3(-1.0, -1.0, 0.0);
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
	GameObject* player;
	GameObject* enemy1;
	GameObject* enemy2;
	int playerRenderOrder{ 0 };
	float deltaTime, lastTime, timer;
};