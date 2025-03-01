#include "Engine.hpp"

#include "Debug.hpp"

Engine::Engine()
{
    InitWindow();

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

        LevelManager::UpdateCall();

        // Clear window for render
        window->ClearWindow();

        // Render call for all sources and swap buffers
        Rendering::Render();
        window->SwapBuffers();

    }
}; // Engine Run
