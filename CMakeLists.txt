# CMakeList.txt : CMake project for GameEngine2D, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GameEngine2D")

# Find libraries
find_package (glfw3 3.3 REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glad REQUIRED)
find_package (glm REQUIRED)
find_package (Stb REQUIRED)

# Game and Engine source files
file (GLOB_RECURSE gameSources Game/*.cpp Game/*.hpp)
file (GLOB_RECURSE engineSources Engine/*.cpp Engine/*.hpp)

# Add the data to the project.
add_executable(GameEngine2D ${gameSources} ${engineSources})

# Link libraries
target_link_libraries(GameEngine2D PUBLIC
	glfw 
	OpenGL::GL
	glad::glad
	glm::glm
	${Stb_INCLUDE_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameEngine2D PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
