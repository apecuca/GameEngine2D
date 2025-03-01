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
		auto renderSource = player->AddComponent<RenderSource>();
		renderSource->InitShader("b_sprite.vert", "b_sprite.frag");
		renderSource->AddSprite("Lupi.png");

		// First obj to test instantiation of multiple objects
		GameObject& obj1 = LevelManager::Instantiate();
		obj1.position = glm::vec3(1.5f, 1.0f, 0.0f);
		obj1.scale = glm::vec3(0.5f, 0.5f, 0.5f);
		auto rnd1 = obj1.AddComponent<RenderSource>();
		rnd1->InitShader("b_sprite.vert", "b_sprite.frag");
		rnd1->AddSprite("Lupi.png");

		// obj2 to test object destruction
		GameObject& obj2 = LevelManager::Instantiate();
		obj2.position = glm::vec3(-1.5f, -1.0f, 0.0f);
		obj2.scale = glm::vec3(0.5f, 0.5f, 0.5f);
		auto rnd2 = obj2.AddComponent<RenderSource>();
		rnd2->InitShader("b_sprite.vert", "b_sprite.frag");
		rnd2->AddSprite("Lupi.png");

		LevelManager::Destroy(obj2);

		// obj2 to test object destruction
		GameObject& obj3 = LevelManager::Instantiate();
		obj3.position = glm::vec3(-1.5f, -1.0f, 0.0f);
		obj3.scale = glm::vec3(0.5f, 0.5f, 0.5f);
		auto rnd3 = obj3.AddComponent<RenderSource>();
		rnd3->InitShader("b_sprite.vert", "b_sprite.frag");
		rnd3->AddSprite("Lupi.png");
	};

	void CustomUpdate() override
	{
		player->Rotate(10.0f * 0.16f);
	};

private:
	std::shared_ptr<GameObject> player;
};