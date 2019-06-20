#include <iostream>

#include "Game.h"


int main(int argc, char* argv[])
{
	//std::cout << "[INFO/ResourceManager] Initializing" << std::endl;

	//ResourceManager* loader = new ResourceManager();

	//loader->loadBlocks();

	//std::cin.get();

	Game game;
	game.run();


	return 0;
}
