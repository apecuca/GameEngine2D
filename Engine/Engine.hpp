#pragma once

// Standard
#include <iostream>

// Externa
#include "CommonInclude/CommonRender.hpp"

// Engine classes
#include "Window.hpp"
#include "Rendering/Rendering.hpp"
#include "Rendering/Rendersource.hpp"
#include "Behaviour/GameObject.hpp"
#include "Debug.hpp"
#include "Level/Level.hpp"
#include "Level/LevelManager.hpp"

class Engine
{
public:
	// Constructor and destructor
	Engine();
	~Engine() = default;

	// Main parts of the engine
	std::unique_ptr<Window> window;

	// Run main thread, don't call this
	void Run();

private:
	// Initialize Engine's single Window, don't call this
	void InitWindow();
};