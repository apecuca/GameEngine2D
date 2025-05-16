#include "Engine.hpp"

Engine::Engine()
{
    InitWindow();
    Rendering::Init();
    Input::InitInput(window->GetCurrentWindow());

    Debug::Log("Succesfully initialized engine");
}

void Engine::InitWindow()
{
    window = std::make_unique<Window>();
}

// Main loop, don't call this manually
void Engine::Run()
{
    while (!window->shouldClose())
    {
        // Update engine stuff
        Time::UpdateVariables();
        Input::UpdateInput();

        // Update behaviours
        LevelManager::UpdateCall();

        // Clear window for render
        window->ClearWindow();

        // Render call for all sources and swap buffers
        Rendering::Render();
        window->SwapBuffers();

    }
}; // Engine Run
