#include "Window.hpp"

// Libraries
#include "CommonInclude/CommonRender.hpp"
#include "Rendering/Rendering.hpp"

// Standard
#include "iostream"

int Window::height, Window::width;
GLFWwindow* Window::windowPtr;

Window::Window()
{
	// Initial values
	width = 640;
	height = 480;

	// Init and throw err
	if (!glfwInit())
		throw std::runtime_error("Error initializing GLFW");

	// Set next window hints (configuration)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create window and throw err
	windowPtr = glfwCreateWindow(width, height, "2D Game Engine", NULL, NULL);
	if (!windowPtr)
	{
		glfwTerminate();
		throw std::runtime_error("Error initializing GLFW Window");
	}

	// Set window as current context
	glfwMakeContextCurrent(windowPtr);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}

	// Set viewport size
	glViewport(0, 0, width, height);

	// Enable vsync
	glfwSwapInterval(1); 

	// Blend function (alpha channel support)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set callbacks
	glfwSetFramebufferSizeCallback(windowPtr, callback_framebufferSize);
	glfwSetErrorCallback(callback_error);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::ClearWindow()
{
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(windowPtr);
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(windowPtr);
}

// GLFW's Error callback
void Window::callback_error(int error_code, const char* description)
{
	std::cout << "GLFW ERROR " << error_code << ": " << description << "\n";
}

// GLFW's Window resize callback
void Window::callback_framebufferSize(GLFWwindow* window, int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;

	// Atualizar dimensões do framebuffer e renderbuffer
	Rendering::ResizeFramebuffer();

	glViewport(0, 0, width, height);
}