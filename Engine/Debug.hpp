#pragma once

#include <iostream>
#include <chrono>
#include "glm/glm.hpp"

class Debug
{
public:
	inline static void PrintTime()
	{
		std::cout << "[" << std::chrono::system_clock::now() << "] ";
	}

	inline static void Log(const char* text)
	{
		PrintTime();
		std::cout << text << "\n";
	}

	inline static void Log(const std::string text)
	{
		PrintTime();
		std::cout << text << "\n";
	}

	inline static void Log(const glm::vec3& value)
	{
		PrintTime();
		std::cout << "vec3(" << value.x << ", " << value.y << ", " << value.z << ")\n";
	}
};