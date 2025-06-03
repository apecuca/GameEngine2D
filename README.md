# 2D Game Engine

### Introduction
This is a simple 2D Game Engine with an example to showcase. The plan is to make this a full Game Engine (framework xd) where the user can just initialize and start developing.
Again, this project is literally just for fun and studying, so this and other documents I write won't be that serious.

### Using the engine
If you REALLY want to try using this engine, you'll need to do a few things before:
1. Update the CMAKE_TOOLCHAIN_FILE variable on CMakePresets.json. That's the variable that tells cmake where are the external libraries (I think, I used vcpkg to automate everything)
2. Use a compiler like Ninja or MinGW to compile the project

After that, just initialize the engine on the main function and have fun :)
I'll start writing a very simple and straightforward documentation once basic physics, sound and UI support have been implemented.

### Todo
This todo list is being updated as I think of new things to implement and progress on the project. I'll probably move this to a Trello board or something similar on the near future.

##### Engine management
- [x] Realtime instancing and destruction of GameObjects
- [x] Component system
	- [x] Refactor system
- [x] Level system
- [x] Class to deal with Time stuff (delta, program time, etc...)
- [x] Class to deal with Input
- [ ] Task

##### Renderization
- [x] Shader rendering
	- [x] Custom render order (improve sorting algorith)
	- [x] Pooling system for sprites
	- [x] Sprite support
		- [x] Add support to the sprite class on rendering manager
		- [x] Sprite ratio same as original image (pixelsPerUnit)
		- [x] Custom color
		- [x] Animation system
			- [x] Animation switching
				- [ ] Based on conditions? Perhaps
			- [ ] Animation events

##### Physics
For physics, I'll be using the Box2D (https://box2d.org/) library, a free physics engine
- [ ] Initialize API

##### UI
For UI support, I'll plan on using Dear ImGui, since it has a lot of functionalities and it's very simple to implement and customize
- [ ] Task

##### Sound
For sound, I'm still deciding on whether to use sdl2-mixer, miniaudio or SoLoud. I'll probably go with miniaudio for it's customizability and compatibility with vcpkg
- [ ] Task

##### Extras
- [x] Change the shader's pointer from shared to unique
- [x] Rewrite object, level and component instanciation logic
- [x] Add engine as a library in main cmakelists, instead of including all files directly in the .exe

### Technologies and libraries used
C++ https://learn.microsoft.com/en-us/cpp/?view=msvc-170 </br>
OpenGL https://www.opengl.org/Documentation/Specs.html </br>
GLFW https://www.glfw.org/documentation.html </br>
GLM https://glm.g-truc.net/0.9.9/api/index.html </br>
Box2D https://box2d.org/documentation/ </br>
Dear ImGui https://github.com/ocornut/imgui </br>

### Extras
If you want to give me advice on how to do something better, feel free to send me a message!