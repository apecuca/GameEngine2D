#pragma once

#include "Engine.hpp"
#include "Player.hpp"

class FirstLevel : public Level
{
public:
	FirstLevel() : Level(),
		player{ nullptr }
	{
		Debug::Log("Level loaded!!");
	}

	void OnLevelInit() override
	{
		player = LevelManager::Instantiate();
		Player* plComp = player->AddComponent<Player>();
		plComp->Init();
	}

	void CustomUpdate() override
	{
		//
	}

private:
	GameObject* player;
};