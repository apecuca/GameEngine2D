#include "Game.hpp"

#include <stdexcept>

int main()
{
	Engine engine;
	Game game;

	try {
		engine.Run();
	}
	catch (const std::runtime_error& err) {
		std::cout << "Error: " << err.what() << std::endl;
	}

	return 0;
}