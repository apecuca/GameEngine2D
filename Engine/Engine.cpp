#include "Engine.hpp"

Engine::Engine()
{
    InitWindow();
    Rendering::Init();

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
        /* Poll for and process events */
        window->PollEvents();

        // Update engine stuff
        Time::UpdateVariables();

        // Update behaviours
        LevelManager::UpdateCall();

        // Clear window for render
        window->ClearWindow();

        // Render call for all sources and swap buffers
        Rendering::Render();
        window->SwapBuffers();

    }
}; // Engine Run
