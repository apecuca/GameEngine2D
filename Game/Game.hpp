#pragma once

#include "../Engine/Engine.hpp"

#include <memory>

class Game
{
public:
	Game();
	~Game() = default;

	std::shared_ptr<GameObject> player;
}; // Game