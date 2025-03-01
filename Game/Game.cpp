#include "Game.hpp"

#include "../Engine/Engine.hpp"
#include "Levels/FirstLevel.hpp"

Game::Game()
{
	LevelManager::LoadLevel<FirstLevel>();

	Debug::Log("Succesfully initialized game");
}