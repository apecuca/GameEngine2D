project(Engine)

file (GLOB_RECURSE engineSources *.cpp *.hpp)

add_library(Engine ${engineSources})

# Find libraries
find_package (glfw3 3.3 REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glad REQUIRED)
find_package (glm REQUIRED)
find_package (Stb REQUIRED)

# Include source dir
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 

# Link libraries
target_link_libraries(Engine PUBLIC
	glfw 
	OpenGL::GL
	glad::glad
	glm::glm
	${Stb_INCLUDE_DIR})