#pragma once

#include <vector>

#include "../Behaviour/GameObject.hpp"

class Level
{
public:
	// Avoid allocating or de-allocating memory on the constructor, please
	Level() = default;
	virtual ~Level() = default;

	// Function called on level instanciation
	virtual void OnLevelInit();

	// Instanciates and returns a reference of the new object
	GameObject* InstantiateObject();
	// Destroy an object
	bool DestroyObject(GameObject* obj);
	// Returns the instanciated objects count
	inline size_t GetObjectCount() { return static_cast<int>(instantiatedObjs.size()); }

	// Level's main function, called every loop
	void UpdateLevel();

	// Custom update for derived levels, called every loop
	virtual void CustomUpdate();

public:
	// List of instantiated objects in the current level
	std::vector<std::unique_ptr<GameObject>> instantiatedObjs;
};