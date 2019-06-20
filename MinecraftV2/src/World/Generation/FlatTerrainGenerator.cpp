#include "FlatTerrainGenerator.h"
#include "../Chunk/Chunk.h"
#include "../Block/BlockId.h"
#include "../../Constants.h"

void FlatTerrainGenerator::generateTerrain(Chunk& chunk)
{
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
}