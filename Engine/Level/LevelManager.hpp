#pragma once

#include <memory>

#include "Level.hpp"

class LevelManager
{
public:

	//
	// Loading/unloading
	// 
	
	// Load a new object derived from the level class.
	// If there was already a loaded level, unloads it before the new
	template <class T>
	static inline Level* LoadLevel()
	{
		if (LevelManager::loadedLevel != nullptr)
			LevelManager::UnloadLevel();

		LevelManager::loadedLevel = std::make_unique<T>();
		LevelManager::loadedLevel->OnLevelInit();
		return LevelManager::loadedLevel.get();
	}
	
	// Unloads the current level.
	static inline void UnloadLevel()
	{
		LevelManager::loadedLevel.reset();
	}

	// Returns a reference to the loaded level
	static inline Level* GetLoadedLevel()
	{
		if (loadedLevel == nullptr)
			throw std::string("There is no level currently loaded.");

		return loadedLevel.get();
	}

	//
	// Loaded level management
	//

	// Calls the main update function on the currently loaded level. Don't call this manually
	static inline void UpdateCall()
	{
		if (loadedLevel == nullptr)
			return;

		loadedLevel->UpdateLevel();
	}

	// Instantiates a new empty object on the currently loaded level
	static inline GameObject* Instantiate()
	{
		if (loadedLevel == nullptr)
			throw std::string("There is no level currently loaded.");

		return loadedLevel->InstantiateObject();
	}

	// Destroys an object on the currently loaded level
	static inline void Destroy(GameObject* obj)
	{
		if (loadedLevel == nullptr)
			throw std::string("There is no level currently loaded.");

		loadedLevel->DestroyObject(obj);
	}

private:
	// Prevents the creation of an object with this class
	LevelManager();

	// Pointer to the current loaded level
	static inline std::unique_ptr<Level> loadedLevel;
}; // classname