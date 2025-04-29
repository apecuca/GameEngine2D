#pragma once

class Time
{
private:
	// Not instantiable
	Time();

public:
	// Update all time related variables, avoid calling this manually
	static void UpdateVariables();

public:
	// Frame time in seconds
	static float deltaTime;
	// Stores last frame's app run time
	static double runTime;
};