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
This todo list is being updated as I think of new things to implement and progress on the project.

Engine management
- [x] Realtime instancing and destruction of GameObjects
- [x] Component system
- [x] Level system
- [ ] Task

Renderization
- [x] Shader rendering
	- [ ] Custom render order# 2D Game Engine

### Introduction
This is a simple lightweight 2D Game Engine with an example to showcase. The plan is to make this a full Game Engine (framework xd) where the user (me) can just download, create a project and start developing.
I've decided to start this project with the purpose of studying 2D graphics programming and, practice code architecture and fixate some OpenGL and C++ concepts on my brain.

### Using the engine
As this is a study-only project, I don't recommend using it for any projects of your own.

### Todo
This todo list is being updated as I think of new things to implement and progress on the project.

##### Engine management
- [x] Realtime instancing and destruction of GameObjects
- [x] Component system
- [x] Level system
- [ ] Task

##### Renderization
- [x] Shader rendering
	- [ ] Custom render order
	- [x] Texture (sprite) support
		- [ ] Animation system

##### Physics
For physics, I'll be using the Box2D (https://box2d.org/) library, a free physics engine
- [ ] Initialize API

##### UI
For UI support, I'll plan on using Dear ImGui, since it has a lot of functionalities and it's very simple to implement and customize.
- [ ] Task

##### Sound
I still haven't thought about this xd
- [ ] Task

### Technologies and libraries used
C++ https://learn.microsoft.com/en-us/cpp/?view=msvc-170
OpenGL https://www.opengl.org/Documentation/Specs.html
GLFW https://www.glfw.org/documentation.html
GLM https://glm.g-truc.net/0.9.9/api/index.html
Box2D https://box2d.org/documentation/
Dear ImGui https://github.com/ocornut/imgui

### Extras
If you want to give me advice on how to do something better, feel free to send me a message!