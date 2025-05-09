# CMakeList.txt : CMake project for GameEngine2D, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Variables
set(EXECUTABLE_NAME GameEngine2D)

project (${EXECUTABLE_NAME}
	 LANGUAGES CXX)

#
# Config language
#
set(CMAKE_CXX_STANDARD			20)
set(CMAKE_CXX_STANDARD_REQUIRED	ON)
set(CMAKE_CXX_EXTENSIONS		OFF)

# Game and Engine source files
add_subdirectory(Engine)
file (GLOB_RECURSE gameSources Game/*.cpp Game/*.hpp)

# Add the data to the project.
# Windows add_executable, used with Windows entry point in main
# add_executable(GameEngine2D WIN32 ${gameSources} ${engineSources})
add_executable(${EXECUTABLE_NAME} ${gameSources})

# Include source dir to target
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} PUBLIC Engine)

add_custom_command(
	TARGET ${EXECUTABLE_NAME} PRE_LINK
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
	"${CMAKE_CURRENT_SOURCE_DIR}/Resources/"
	"$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/Resources"
	COMMENT "Copying directory <source_directory> to <destination_directory>"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 20)
endif()
