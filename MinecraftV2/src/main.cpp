#include <iostream>

#include "Util/FileUtil.h"
#include "Resources/ModelBlock.h"

#include "ResourceLoader.h"



int main(int argc, char* argv[])
{
	std::cout << "[INFO/ResourceLoader] Initializing" << std::endl;

	ResourceLoader* loader = new ResourceLoader();

	loader->loadBlocks();

	return 0;
}
