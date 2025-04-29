#include "Time.hpp"

#include "GLFW\glfw3.h"

float Time::deltaTime = 0;
double Time::runTime = 0;

void Time::UpdateVariables()
{
	double newTime = glfwGetTime();
	deltaTime = static_cast<float>(newTime - runTime);
	runTime = newTime;
}