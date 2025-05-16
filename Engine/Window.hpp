#pragma once

// Forward declaration to avoid importing on header
struct GLFWwindow;

class Window
{
public:
	// Constructor and destructor
	Window();
	~Window();

	// Controls if main loop should close
	bool shouldClose();

	// Reference to pointer to the Window
	static GLFWwindow* GetCurrentWindow() { return windowPtr; };

	// Main loop stuff
	
	// Clear main window and fill with basic color
	void ClearWindow();
	// Swap between video buffers
	void SwapBuffers();

public:
	// Window size, DON'T CHANGE VALUES IT WILL BREAK
	static int width, height;

private:
	// Pointer to the main GLFWwindow
	static GLFWwindow* windowPtr;
	
	// Callbacks
	static void callback_error(int error_code, const char* description);
	static void callback_framebufferSize(GLFWwindow* window, int width, int height);
};