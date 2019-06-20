#include "FlatTerrainGenerator.h"
#include "../Chunk/Chunk.h"
#include "../Block/BlockId.h"
#include "../../Constants.h"
//#include <ctime>

void FlatTerrainGenerator::generateTerrain(Chunk& chunk)
{
	//std::srand(time(nullptr));

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			chunk.setBlock(x, 0, z, BlockId::Stone);
			chunk.setBlock(x, 1, z, BlockId::Dirt);
			chunk.setBlock(x, 2, z, BlockId::Dirt);
			chunk.setBlock(x, 3, z, BlockId::Dirt);
			chunk.setBlock(x, 4, z, BlockId::Grass);
		}
	}

	//auto random = (static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX)+1));

	//if (random > 0.74)
	{
		chunk.setBlock(8, 4, 8, BlockId::WhiteWool);
		chunk.setBlock(8, 5, 8, BlockId::OakLog);
		chunk.setBlock(8, 6, 8, BlockId::OakLog);
		chunk.setBlock(8, 7, 8, BlockId::OakLog);
	}
}
